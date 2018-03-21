if [ $# == 3 ]
then
    find . -type f -name "*.$1" -exec ls {} \; | echo $(grep -c $2 {})
	exit 0
else
	echo "ERROR: Introdueix tres parametres, una extensio de fitxer i dues cadenes"
	exit 1
fi
