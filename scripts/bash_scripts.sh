# This is a collection of scripts used to manage images and folder
#  - Scripts have echo to test the expected output

# Rename numerically 
i=1; for f in *; do echo mv "$f" "$(printf "%05d.jpg" $i)"; ((i++)); done

# Rename with random numeric name
for fname in *; do echo mv "$fname" $RANDOM.jpg; done

# Copy all *.jpg files from the current folder to a new folder
echo cp `find . -name "*.jpg"` <newfolder>
