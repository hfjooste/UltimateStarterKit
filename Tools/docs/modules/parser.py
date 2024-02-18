# Created by Henry Jooste

import os
import re


class Parser:
    file_content = None
    cpp_content = None
    class_name = None
    name = None
    file_dir = None
    file_name = None
    description = None
    content = None
    enum = False
    struct = False
    widget = None
    output = None
    sections = []

    def __init__(self, input_file, widget):
        with open(input_file, 'r') as f:
            self.file_content = f.read()
        if "UENUM" in self.file_content:
            self.enum = True
        if "USTRUCT" in self.file_content:
            self.struct = True
        if not self.enum and not self.struct:
            if "public:" not in self.file_content:
                raise Exception("File is not supported. There are no public functions in this header file")
            cpp_name = input_file[:-2] + ".cpp"
            self.cpp_content = ""
            if os.path.exists(cpp_name):
                with open(cpp_name, 'r') as f:
                    self.cpp_content = f.read()
            self.content = self.file_content.split("public:")[1].split("private:")[0].split("};")[0]
        else:
            self.cpp_content = ""
            self.content = self.file_content
        if self.struct:
            self.content = self.file_content.split("GENERATED_USTRUCT_BODY()")[1].split("};")[0]
        self.class_name = self.file_content.split(":")[0].strip().split(" ")[-1].strip()
        self.name = f"<code>{self.class_name[1:]}</code>"
        self.file_dir = os.path.basename(os.path.dirname(input_file))
        self.file_name = os.path.basename(input_file)
        self.description = self.file_content.split("@brief")[1].split("*/")[0].strip()
        self.widget = widget
        self.extract_sections(self.content)

    def generate(self):
        self.output = f"## Introduction\n{self.description}\n"
        if self.enum:
            self.generate_enum_values()
            return
        if self.struct:
            self.generate_struct_values()
            return
        self.generate_dependencies()        
        additional = os.path.abspath(os.path.join(os.path.dirname(__file__), "..\\additional", self.file_name[:-2] + ".md"))
        if os.path.exists(additional):
            print(f"Adding additional documentation from {additional}")
            with open(additional, 'r') as f:
                self.output += f"\n{f.read()}\n"
        self.generate_components()
        self.generate_required_widgets()
        self.generate_optional_widgets()
        self.generate_optional_anims()
        self.output += "\n## API Reference"
        self.generate_property_docs()
        self.generate_event_docs()
        self.generate_function_docs()
        usage = os.path.abspath(os.path.join(os.path.dirname(__file__), "..\\usage", self.file_name[:-2] + ".md"))
        if os.path.exists(usage):
            print(f"Adding custom usage documentation from {usage}")
            with open(usage, 'r') as f:
                self.output += f"\n{f.read()}"
        else:
            self.generate_blueprint_usage()
            self.generate_cpp_usage()


    def save(self, output_file):
        with open(output_file, 'w') as f:
            f.write(self.output)


    def extract_sections(self, text):
        self.sections = re.findall(r'(/\*\*[\s\S]*?\*/[\s\S]*?;)', text.replace(") { return nullptr; }", ");").replace(") { }", ");"))


    def generate_enum_values(self):
        html = "\n## Values\n<table>\n\t<tr>\n\t\t<th>Value</th>\n\t\t<th>Description</th>\n\t</tr>"
        enum_sections = self.content.replace("};", "").split("/*")[2:]
        for section in enum_sections:
            value = section.split("*/")[1].strip()
            if value.endswith(","):
                value = value[:-1]
            if "=" in value:
                value = value.split("=")[0].strip()
            description = section.split("@brief")[1].split("*")[0].strip()
            html += "\n\t<tr>"
            html += f"\n\t\t<td>{value}</td>"
            html += f"\n\t\t<td>{description}</td>"
            html += "\n\t</tr>"
        html += "\n</table>"
        self.output += html


    def generate_struct_values(self):
        self.generate_property_docs()
        self.output = self.output.replace("### Properties", "## Properties")


    def generate_dependencies(self):
        dependency_docs = ""
        if "USK/Logger/Log.h" in self.cpp_content and self.class_name != "ULog":
            dependency_docs += "\n\t<li><a href=\"../logger\">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>"
        if ("USKGameInstance" in self.file_content or "USKGameInstance" in self.cpp_content) and self.class_name != "UUSKGameInstance":
            if self.class_name != "UUSKGameInstance":
                dependency_docs += "\n\t<li><a href=\"../gameinstance\">Game Instance</a>: Used to monitor for input device changes and handle saving/loading game data</li>"
        if "UAudioUtils" in self.cpp_content and self.class_name != "UAudioUtils":
            dependency_docs += "\n\t<li><a href=\"../audio\">Audio</a>: Used to play sound effects either 2D or at a specified location</li>"
        if dependency_docs != "":
            self.output += "\n## Dependencies\n"
            self.output += f"The {self.name} relies on other components of this plugin to work:\n<ul>{dependency_docs}\n</ul>\n"


    def generate_components(self):
        self.extract_sections(self.file_content)
        properties = self.extract_uproperties(False)
        component_html = ""
        for property in properties:
            if not property["component"]:
                continue
            component_html += "\n\t<tr>"
            component_html += f"\n\t\t<td>{property['name']}</td>"
            component_html += f"\n\t\t<td>{property['description']}</td>"
            component_html += f"\n\t\t<td>{property['type']}</td>"
            component_html += "\n\t</tr>"
        if component_html != "":
            html = "\n## Components"
            html += f"\nThe {self.name} uses the following components:"
            html += "\n<table>\n\t<tr>\n\t\t<th>Name</th>\n\t\t<th>Description</th>\n\t\t<th>Type</th>\n\t</tr>"
            html += component_html
            html += "\n</table>\n"
            self.output += html
        self.extract_sections(self.content)


    def generate_required_widgets(self):
        properties = self.extract_uproperties(False)
        widget_html = ""
        for property in properties:
            if not property["required_widget"]:
                continue
            widget_html += "\n\t<tr>"
            widget_html += f"\n\t\t<td>{property['name']}</td>"
            widget_html += f"\n\t\t<td>{property['description']}</td>"
            widget_html += f"\n\t\t<td>{property['type']}</td>"
            widget_html += "\n\t</tr>"
        if widget_html != "":
            html = "\n## Required Widgets\n"
            if self.widget and not self.widget.isspace():
                html += f"There is already a <code>{self.widget}</code> that you can use in your projects. "
                html += "But if you create your own instance of this widget, you need to add the following before you can compile:"
            else:
                html += f"You need to add the following before you can compile the {self.name} widget:"
            html += "\n<table>\n\t<tr>\n\t\t<th>Name</th>\n\t\t<th>Description</th>\n\t\t<th>Type</th>\n\t</tr>"
            html += widget_html
            html += "\n</table>\n"
            self.output += html

    
    def generate_optional_widgets(self):
        properties = self.extract_uproperties(False)
        widget_html = ""
        for property in properties:
            if not property["optional_widget"]:
                continue
            widget_html += "\n\t<tr>"
            widget_html += f"\n\t\t<td>{property['name']}</td>"
            widget_html += f"\n\t\t<td>{property['description']}</td>"
            widget_html += f"\n\t\t<td>{property['type']}</td>"
            widget_html += "\n\t</tr>"
        if widget_html != "":
            html = "\n## Optional Widgets"
            html += "\nYou can add the following widgets to enable extra functionality:"
            html += "\n<table>\n\t<tr>\n\t\t<th>Name</th>\n\t\t<th>Description</th>\n\t\t<th>Type</th>\n\t</tr>"
            html += widget_html
            html += "\n</table>\n"
            self.output += html


    def generate_optional_anims(self):
        properties = self.extract_uproperties(False)
        anim_html = ""
        for property in properties:
            if not property["animation"]:
                continue
            anim_html += "\n\t<tr>"
            anim_html += f"\n\t\t<td>{property['name']}</td>"
            anim_html += f"\n\t\t<td>{property['description']}</td>"
            anim_html += "\n\t</tr>"
        if anim_html != "":
            html = "\n## Optional Animations"
            html += "\nYou can add the following widgets to enable extra functionality:"
            html += "\n<table>\n\t<tr>\n\t\t<th>Name</th>\n\t\t<th>Description</th>\n\t</tr>"
            html += anim_html
            html += "\n</table>\n"
            self.output += html


    def extract_uproperties(self, only_events):
        properties = []        
        for section in self.sections:
            if "UPROPERTY" not in section:
                continue
            if not only_events and "BlueprintAssignable" in section:
                continue
            if only_events and not "BlueprintAssignable" in section:
                continue
            lines = section.split("\n")
            description = section.split("@brief")[1].split("*")[0].strip()
            type_index = 0
            while True:
                type = lines[len(lines) - 1].replace(", ", ",").strip().split(" ")[type_index].strip()
                if type in ["static", "virtual", "class"]:
                    type_index += 1
                    continue
                break
            type = type.replace(",", ", ")
            name = lines[len(lines) - 1].split(f"{type} ")[1].split("(")[0].strip()[:-1]
            default = ""
            if "=" in name:
                default = name.split("=")[1].strip()
                name = name.split("=")[0].strip()
            if type.endswith("*") and default == "":
                default = "<code>nullptr</code>"
            if type == "bool" and default == "":
                default = "false"
            event_params = []
            if only_events:
                event_params = self.extract_event_params(type)
            properties.append({
                "name": name,
                "description": description,
                "type": type.replace("<", "&lt;").replace(">", "&gt;"),
                "default": default,
                "event_params": event_params,
                "required_widget": "BindWidget" in section and
                    "BindWidgetOptional" not in section and "BindWidgetAnimOptional" not in section,
                "optional_widget": "BindWidgetOptional" in section,
                "animation": "BindWidgetAnimOptional" in section,
                "component": "AllowPrivateAccess" in section
            })
        return properties
    

    def extract_event_params(self, type):
        event_params = []
        params = self.file_content.split(f"({type}")[1].split(");")[0].strip()
        if params == "":
            return event_params
        params = params[1:].strip().split(",")
        if len(params) == 0:
            return event_params
        file_lines = self.file_content.split("\n")
        line_index = -1
        for line in file_lines:
            line_index += 1
            if "DECLARE_DYNAMIC_MULTICAST_DELEGATE" not in line or f"({type}" not in line:
                continue
            while True:            
                line_index -= 1
                docs_line = file_lines[line_index]     
                if "@brief" in docs_line:
                    start_index = line_index + 1
                    break
            param_index = 0
            for i in range(start_index, start_index + int(len(params) / 2)):
                param_type = params[param_index].strip()
                param_name = file_lines[i].split("@param")[1].strip().split(" ")[0].strip()
                param_description = file_lines[i].split(f"@param {param_name} ")[1].strip()
                event_params.append({
                    "type": param_type,
                    "name": param_name,
                    "description": param_description
                })
        return event_params


    def generate_property_docs(self):
        properties = self.extract_uproperties(False)
        if len(properties) == 0:
            return
        html = "\n### Properties\n"
        html += "<table>\n"
        html += f"\t<tr>\n"
        html += f"\t\t<th>Property</th>\n"
        html += f"\t\t<th>Description</th>\n"
        html += f"\t\t<th>Type</th>\n"
        html += f"\t\t<th>Default Value</th>\n"
        html += f"\t</tr>\n"
        for property in properties:
            if property['required_widget'] or property['optional_widget'] or property['component']:
                continue
            html += f"\t<tr>\n"
            html += f"\t\t<td>{property['name']}</td>\n"
            html += f"\t\t<td>{property['description']}</td>\n"
            html += f"\t\t<td>{property['type']}</td>\n"
            html += f"\t\t<td>{property['default']}</td>\n"
            html += f"\t</tr>\n"
        html += "</table>\n"
        self.output += html


    def generate_event_docs(self):
        events = self.extract_uproperties(True)
        if len(events) == 0:
            return
        html = "\n### Events\n"
        html += "<table>\n"
        html += f"\t<tr>\n"
        html += f"\t\t<th>Name</th>\n"
        html += f"\t\t<th>Description</th>\n"
        html += f"\t\t<th>Params</th>\n"
        html += f"\t</tr>\n"
        for event in events:
            html += f"\t<tr>\n"
            html += f"\t\t<td>{event['name']}</td>\n"
            html += f"\t\t<td>{event['description']}</td>\n"
            html += f"\t\t<td>"
            started_params = False
            for param in event['event_params']:
                if started_params:
                    html += "<br/><br/>"
                started_params = True
                html += f"<strong>{param['name']} ({param['type']})</strong><br/>{param['description']}"
            html += f"</td>\n"
            html += f"\t</tr>\n"
        html += "</table>\n"
        self.output += html


    def extract_functions(self):
        functions = []        
        for section in self.sections:
            if "UFUNCTION" not in section:
                continue
            lines = section.split("\n")
            description = section.split("@brief")[1].split("*")[0].strip()
            category = section.split("Category")[1].strip()[1:].strip()[1:].split("\"")[0].strip()
            return_type_index = 0
            while True:
                return_type = lines[len(lines) - 1].split(" ")[return_type_index].strip()
                if return_type == "static" or return_type == "virtual":
                    return_type_index += 1
                    continue
                break
            name = lines[len(lines) - 1].split(return_type)[1].split("(")[0].strip()
            display_name = re.sub("([a-z])([A-Z])","\g<1> \g<2>", name)
            if "DisplayName" in section:
                display_name = section.split("DisplayName")[1].split("=")[1].split("\"")[1]
            return_description = ""
            if "@return" in section:
                return_description = section.split("@return")[1].split("*")[0].strip()
            params = []
            for line in lines:
                if "@param" in line:
                    param_name = line.strip().split("@param ")[1].split(" ")[0].strip()
                    param_type = lines[len(lines) - 1].split(f" {param_name}")[0].replace("const", "").strip()
                    if " " in param_type:
                        param_type = param_type.split(" ")[-1].strip()
                    if "," in param_type:
                        param_type = param_type.split(",")[1].strip()
                    elif "(" in param_type:
                        param_type = param_type.split("(")[1].strip()
                    params.append({
                        "name": param_name,
                        "type": param_type,
                        "description": line.replace("*", "").strip().replace(f"@param {param_name}", "").strip()
                    })
            functions.append({
                "name": name,
                "display_name": display_name,
                "description": description,
                "category": category.replace("|", " > "),
                "params": params,
                "void": "void " in section,
                "static": "static " in lines[len(lines) - 1],
                "return_type": return_type,
                "return_description": return_description
            })
        return functions


    def generate_function_docs(self):
        functions = self.extract_functions()
        if len(functions) == 0:
            return
        html = "\n### Functions\n"
        html += "<table>\n"
        html += f"\t<tr>\n"
        html += f"\t\t<th>Name</th>\n"
        html += f"\t\t<th>Description</th>\n"
        html += f"\t\t<th>Params</th>\n"
        html += f"\t\t<th>Return</th>\n"
        html += f"\t</tr>\n"
        for function in functions:
            html += f"\t<tr>\n"
            html += f"\t\t<td>{function['name']}</td>\n"
            html += f"\t\t<td>{function['description']}</td>\n"
            html += f"\t\t<td>"
            started_params = False
            for param in function['params']:
                if started_params:
                    html += "<br/><br/>"
                started_params = True
                html += f"<strong>{param['name']} ({param['type']})</strong><br/>{param['description']}"
            html += f"</td>\n"
            if function['void']:
                html += f"\t\t<td></td>\n"
            else:
                return_type = function['return_type'].replace("<", "&lt;").replace(">", "&gt;")
                html += f"\t\t<td><strong>{return_type}</strong><br/>{function['return_description']}</td>\n"
            html += f"\t</tr>\n"
        html += "</table>\n"
        self.output += html


    def generate_blueprint_usage(self):
        functions = self.extract_functions()
        if len(functions) == 0:
            return
        html = f"\n## Blueprint Usage\nYou can use the {self.name} using Blueprints by adding one of the following nodes:\n<ul>"
        for function in functions:
            html += f"\n\t<li>{function['category']} > {function['display_name']}</li>"
        html += "\n</ul>\n"
        self.output += html


    def generate_cpp_usage(self):
        functions = self.extract_functions()
        if len(functions) == 0:
            return
        html = "\n## C++ Usage\n"
        html += "Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:\n"
        html += "```c++\n"
        html += "PublicDependencyModuleNames.Add(\"USK\");\n"
        html += "```\n\n"
        html += f"The {self.name} can now be used in any of your C++ files:\n"
        html += "```c++\n"
        html += f"#include \"USK/{self.file_dir}/{self.file_name}\"\n\n"
        html += "void ATestActor::Test()\n"
        html += "{\n"
        cpp_code = ""
        should_explain_pointer = False
        for function in functions:
            cpp_code += "\t"
            if not function['void']:
                value_name = f"{function['name']}Value"
                if value_name.lower().startswith("get"):
                    value_name = value_name[3:-5]
                cpp_code += f"{function['return_type']} {value_name} = "
            if function['static']:
                cpp_code += f"{self.class_name}::{function['name']}("
            else:
                should_explain_pointer = True
                cpp_code += f"{self.class_name[1:]}->{function['name']}("
            for param in function['params']:
                cpp_code += f"{param['name']}, "
            if len(function['params']) > 0:
                cpp_code = cpp_code[:-2]
            cpp_code += ");\n"
        if should_explain_pointer:
            html += f"\t// {self.class_name[1:]} is a pointer to the {self.class_name}\n"        
        html += cpp_code
        html += "}\n"
        html += "```\n"
        self.output += html