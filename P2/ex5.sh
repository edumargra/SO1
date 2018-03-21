ps aux h -u $(whoami) | sort -nrk3 | head -n 5 | awk '{print $2" "$3" "$11}'
