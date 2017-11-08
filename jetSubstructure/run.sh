#void drawSoftDrop(float coneR=1.0, int  trkPtCut=0, float thetaCut =0., int numEvents =  1000000, int ptLow=\
#150, int ptHigh=250)

version=3.00
for r in '0.4' '1.0'
do
    for ptCut in 6 4 0
    do
        for thetaCut in 0.1 0.2 0
        do
	    mkdir r${r}_trkPtCut${ptCut}_theta${thetaCut}_v${version}
            root -l -b -q 'drawSoftDrop.C+('$r', '$ptCut', '$thetaCut', 1000000, 150, 250)'
        done
    done
done