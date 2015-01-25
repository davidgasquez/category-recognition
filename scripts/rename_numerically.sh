i=1; for f in *; do echo mv "$f" "$( printf "%05d.jpg" $i )"; ((i++)); done
