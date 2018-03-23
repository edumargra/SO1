if [ $# == 3 ]
then
	find . -type f -name "*.$1" -printf '%p ' -exec grep -co $2 {} \; -exec sed -i "s:$2:$3:g" {} \; 
	exit 0
else
	echo "ERROR: Introdueix tres parametres, una extensio de fitxer i dues cadenes"
	exit 1
fi
