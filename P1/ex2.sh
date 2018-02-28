if [ $# == 1 ]
then
	result=""
	string=$1
	len=$((${#string} - 1))
	for (( i=$len; i>=0 ; i-- ))
	do
		result=$result${string:$i:1}
	done
	echo $result
else
	echo "ERROR: Introdueix un unic parametre, una cadena."
	exit 1
fi
