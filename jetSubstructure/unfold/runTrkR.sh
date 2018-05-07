for im in 1 2 3 4 
do
    root -l -b -q 'getTrkR.C+(0,0,'$im')'
    root -l -b -q 'getTrkR.C+(1,0,'$im')'
    root -l -b -q 'getTrkR.C+(1,1,'$im')'
    root -l -b -q 'getTrkR.C+(1,2,'$im')'
    root -l -b -q 'getTrkR.C+(1,3,'$im')'
    root -l -b -q 'getTrkR.C+(1,4,'$im')'
    root -l -b -q 'getTrkR.C+(1,5,'$im')'
    root -l -b -q 'getTrkR.C+(1,6,'$im')'
done
