directory=$1
numero=$2
cd $1
if [ ! -f petits ] 
then
	mkdir petits
fi
if [ ! -f grans ] 
then
	mkdir grans
fi	
ls -l > info.txt
mida=($(awk '{print $5}' info.txt))
nom=($(awk '{print $9}' info.txt))
for (( i = 0; i <= ${#nom[@]}; i++ ))
do
	if [ ! -d ${nom[i]} ] 
	then
		echo $(( ${mida[i]} )) 
		if [ $(( ${mida[i]} - numero )) -gt 0 ]
		then
			mv ${nom[i]} grans
		else
			mv ${nom[i]} petits
		fi
	fi
done									 
