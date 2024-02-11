#!/bin/bash

# Add an alias to .bashrc
add_alias() {
    alias_name="$1"
    alias_command="$2"

    echo "alias $alias_name='$alias_command'" >> ~/.bashrc
}

# Add aliases
add_alias "cmb" "cmake --build ."
# Add more aliases here


source ~/.bashrc

echo "Aliases added successfully."