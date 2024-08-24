#!/bin/bash

# Set the paths for the input and output folders
results_folder="../trabalho1arrumado/resultados"
new_results_folder="./resultados"
output_folder="./resultados_finais"

# Create the output folder if it doesn't exist
mkdir -p "$output_folder"

# Loop through all files in the results folder
for results_file in "$results_folder"/*; do
  # Extract the file name without the path
  file_name=$(basename "$results_file")
  
  # Form the corresponding new_results_file path
  new_results_file="$new_results_folder/$file_name"

  # Skip if the corresponding new_results_file doesn't exist
  if [ ! -f "$new_results_file" ]; then
    echo "Skipping $results_file. Corresponding new_results_file not found."
    continue
  fi

  # Set the output file path
  output_file="$output_folder/$file_name"

  # Merge the files and create the output file
  paste -d ' ' <(awk '{print $1, $2, $3}' "$results_file") <(awk '{print $2, $3}' "$new_results_file") > "$output_file"

  # Print a message indicating success
  echo "Files merged successfully. Output file: $output_file"
done
