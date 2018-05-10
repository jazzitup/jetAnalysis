for im in 3 2 1 4
do
    root -l -b -q 'getTrkR.C+(0,0,'$im')'
done 
for im in 1 2 3 4 
do
    root -l -b -q 'getTrkR.C+(1,0,'$im')'
done
