import os, re, sys

# probably inefficient and better solution, but I want to be able to have all behaviours included in a dll for the engine

# Regex to find classes that use behaviours
pattern = re.compile(r'REGISTER_BEHAVIOUR\s*\(\s*(\w+)\s*\)')

def generate_registry(output_file, search_dirs):
    classes = []
    for d in search_dirs:
        for root, _, files in os.walk(d):
            for file in files:

                if file == "Behaviour.h": #skip base header
                    continue
                
                if file.endswith(('.cpp', '.h')): #check all files that could be behaviours
                    with open(os.path.join(root, file), 'r', errors='ignore') as f:
                        content = f.read()
                        matches = pattern.findall(content)
                        classes.extend([m for m in matches if m != "ClassName"]) #ignore literal name to prevent a compile failure

    classes = sorted(list(set(classes)))
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    
    with open(output_file, 'w') as f:
        f.write("// Generated from files\n")
        f.write("#pragma once\n\n")
        
        # Tell windows that these come from a dlL
        for cls in classes:
            f.write(f"extern int ForceLink_{cls};\n")
            
        f.write("\ninline void ForceLinkAll() {\n")
        f.write("    int volatile _unused = 0;\n")
        for cls in classes:
            f.write(f"    _unused += ForceLink_{cls};\n")
        f.write("}\n")

if __name__ == "__main__":
    generate_registry(sys.argv[1], sys.argv[2:])