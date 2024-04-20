
for i in 0.5 0.7 1 1.2 1.4 1.6 1.8 2.0
do
    t=$i
    sed -i '1s/.*/'${t}'/' input.dat
    echo "y" | make run
done