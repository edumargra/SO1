if [ $# == 2 ]
then
    find $1 -name "*.$2" -exec ls -l {} \; | sort -nk5 | awk '{print $9}'
	exit 0
else
	echo "ERROR: Introdueix dos parametres, un directori i una extensio de fitxer."
	exit 1
fi
