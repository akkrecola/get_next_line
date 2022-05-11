if [[ $1 == "test" ]]; then
	for file in *.c
	do
  		mv "$file" "${file/.c/.test}"
	done
elif [[ $1 == "c" ]]; then
	for file in *.test
	do
  		mv "$file" "${file/.test/.c}"
	done
fi
