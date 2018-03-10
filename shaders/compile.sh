#!/usr/bin/env bash

pwd

shopt -s nullglob #set to not run once

echo "Vertex shaders:"
for file in *.vert;
do
    echo "$file"
    ${VULKAN_SDK}/bin/glslangValidator -V "$file"
done

echo "Fragment shaders:"
for file in *.frag;
do
    ${VULKAN_SDK}/bin/glslangValidator -V "$file"
done

shopt -u nullglob #revert to default