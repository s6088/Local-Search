make
#g++ qwh.cpp -o a


#grid size
for i in 70
do

#fixed percent
for j in  70
do

truncate -s 0 o.txt

printf "$i sq grid with $j percent fixed \n"


for eachfile in in/PLSE-$i-$j-0/*
do
   ./a $eachfile $i  >> o.txt
done

echo -n "avrg time : "
awk '{ total1 += $2 } END { print  total1/100 }' o.txt

echo -n "avrg vio : "
awk '{ total2 += $1 } END { print  total2/100 }' o.txt

done


done
