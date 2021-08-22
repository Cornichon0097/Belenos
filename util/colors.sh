#
# Builds include file from RGB file.
# !/bin/bash
#

# Default output file.
output_file="include/color.h"
# Default RGB file.
rgb_file="res/rgb.txt"

# Checks options.
while getopts ":o:r:h" arg
do
  case ${arg} in
    o) # Output file.
      output_file=${OPTARG}
      ;;
    r) # RGB file.
      rgb_file=${OPTARG}
      ;;
    h) # Help.
      echo "Usage: ${0} [-o output_file] [-r rgb_file]"
      echo "Default output file: ${output_file}."
      echo "Default RGB file: ${rgb_file}."
      exit 0
      ;;
    :) # Missing argument.
      echo "${0}: missing file name after -${OPTARG}." >&2
      exit 1
      ;;
    ?) # Invalid option.
      echo "${0}: invalid option -${OPTARG}." >&2
      exit 2
      ;;
  esac
done

# Checks if output file already exists.
if [ -f ${output_file} ]
then
  echo "${0}: ${output_file} already exists."
  read -p "Overwrite actual ${output_file}? [Y/n] " answer

  case ${answer} in
    Y) # Yes: cleans output file.
      rm -f ${output_file}
      ;;
    n) # No.
      echo "${0}: abort."
      exit 0
      ;;
    ?) # Invalid answer.
      echo "${0}: invalid answer ${answer}." >&2
      exit 3
      ;;
  esac
fi

# Looks for RGB file.
if [ -f ${rgb_file} ]
then
  # Sanitizes RGB file.
  echo -n "Preparing RGB file..."
  awk 'NF==4 {print $0}' ${rgb_file} | sed 's/\([a-z]\)\([A-Z]\)/\1_\2/g' > rgb-tmp.txt
  echo " done."

  # Creates output file and puts protection again multiple inclusions.
  echo -n "Preparing output file..."
  file_name=$(basename --suffix='.h' ${output_file})
  printf "#ifndef ${file_name^^}_H\n" >> ${output_file}
  printf "#define ${file_name^^}_H\n" >> ${output_file}
  printf "\n\n" >> ${output_file}
  echo " done."

  # Puts each color in output file.
  echo -n "Writing in output file..."
  printf "/*\n * Some colors.\n */\n" >> ${output_file}
  for line in $(awk '{print NR}' rgb-tmp.txt)
  do
    # Puts '#define' in output file.
    printf "#define " >> ${output_file}

    # Puts color name in output file.
    color_name=$(awk "NR==${line} {print \$4}" rgb-tmp.txt)
    printf "${color_name^^}" >> ${output_file}

    # Extracts color value from RGB file.
    red=$(awk "NR==${line} {print \$1}" rgb-tmp.txt)
    green=$(awk "NR==${line} {print \$2}" rgb-tmp.txt)
    blue=$(awk "NR==${line} {print \$3}" rgb-tmp.txt)
    color=$(((red << 16) | (green << 8) | blue))

    # Puts blank spaces to align each color value.
    length=$(expr length ${color_name})
    for ((i = length; i < 23; i++))
    do
      printf " " >> ${output_file}
    done

    # Puts color value in output file.
    printf "0x%06X\n" ${color} >> ${output_file}
  done

  # Puts color type definition in output file.
  printf "\n\n" >> ${output_file}
  printf "/*\n * Color type definition.\n */\n" >> ${output_file}
  printf "typedef unsigned int color_t;\n" >> ${output_file}

  echo " done."

  # Puts end of protection in output file.
  printf "\n\n" >> ${output_file}
  printf "#endif /* $(basename ${output_file}) */\n" >> ${output_file}

  # Cleans temporary file.
  rm rgb-tmp.txt
else
  echo "${0}: cannot find ${rgb_file}: no such file or directory."
fi

exit 0
