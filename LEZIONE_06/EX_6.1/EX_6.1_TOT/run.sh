for j in 1 0 
do
    sed -i "5c ${j}" input.dat
    for t in 0.02 0
    do 
        t = $i
        sed -i "4c ${t}" input.dat
        ./run_temp.sh
    done
    
    if $j == 1; then 
        ./mv_config_metropolis.sh 
    else 
        ./mv_config_gibbs.sh 
    fi 
done