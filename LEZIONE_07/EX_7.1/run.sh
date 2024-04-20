
delta_md = "0.0005"
delta_solid = "0.1"
delta_liquid = "0.2"
delta_gas = "5"
for j in 0 1
do
    sed -i "1c ${j}" INPUT_FILE/input.SOLID
    sed -i "1c ${j}" INPUT_FILE/input.LIQUID
    sed -i "1c ${j}" INPUT_FILE/input.GAS
    if $j == 0; then
        for a in "SOLID" "LIQUID" "GAS"
            do
                sed -i "7c ${delta_md}" INPUT_FILE/input.${a}
            done
    else
        sed -i "7c ${delta_solid}" INPUT_FILE/input.SOLID
        sed -i "7c ${delta_liquid}" INPUT_FILE/input.LIQUID
        sed -i "7c ${delta_gas}" INPUT_FILE/input.GAS
    fi      
    ./run_phases.sh
done