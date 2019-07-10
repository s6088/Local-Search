g++ qwh.cpp -o a
truncate -s 0 o.txt
echo plseSize  fixPercentage  txtFile : 
read plseSize percent txtfile
if [ $txtfile = "0" ]
then 

for eachfile in in/PLSE-$plseSize-$percent-0/*
do
   ./a $eachfile $plseSize >> o.txt
   printf "."
done

echo ""

g++ analytics.cpp -o a
./a
else 

   ./a in/PLSE-$plseSize-$percent-0/QWH-$plseSize-$percent-$txtfile.txt $plseSize 
   

fi

