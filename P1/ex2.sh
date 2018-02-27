if [ $# == 1 ]
then
	result=""
	string=$1
	len=${#string}
	i=0
	while [ $i -lt $len ]
	do
		index=$(expr $len - $i - 1)
		result=$result${string:$index:1}
		(( i++ ))
	done
	echo $result
else
	echo "ERROR: Introdueix un unic parametre, una cadena."
	exit 1
fi