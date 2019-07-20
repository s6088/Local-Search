make
#g++ qwh.cpp -o a
g++ analytics.cpp -o b

for i in 70
do


for j in  70
do

truncate -s 0 o.txt

printf "$i*$i grid with $j percent fixed \n"


for eachfile in in/PLSE-$i-$j-0/*
do
   ./a $eachfile $i  #>> o.txt
done


./b

echo ""

done

echo ""

done
