a=([0]="30000"  [1]="1")
b=([0]="50" [1]="2000")

for j in 0 1
do
    for t in 0 1
    do 
        if $j == 0; then
            if $t == 0; then
                sed -i "7c ${"0.0005"}" INPUT_FILE/input.SOLID
                sed -i "8c ${a[0]}" INPUT_FILE/input.SOLID
                sed -i "9c ${a[1]}" INPUT_FILE/input.SOLID
                sed -i "1c ${j}" INPUT_FILE/input.SOLID
                sed -i "2c ${t}" INPUT_FILE/input.SOLID
                sed -i "3c ${"1.5"}" INPUT_FILE/input.SOLID
                sed -i "7c ${"0.0005"}" INPUT_FILE/input.LIQUID
                sed -i "8c ${a[0]}" INPUT_FILE/input.LIQUID
                sed -i "9c ${a[1]}" INPUT_FILE/input.LIQUID
                sed -i "1c ${j}" INPUT_FILE/input.LIQUID
                sed -i "2c ${t}" INPUT_FILE/input.LIQUID
                sed -i "3c ${"2"}" INPUT_FILE/input.LIQUID
                sed -i "7c ${"0.0005"}" INPUT_FILE/input.GAS
                sed -i "8c ${a[0]}" INPUT_FILE/input.GAS
                sed -i "9c ${a[1]}" INPUT_FILE/input.GAS
                sed -i "1c ${j}" INPUT_FILE/input.GAS
                sed -i "2c ${t}" INPUT_FILE/input.GAS
                sed -i "3c ${"0.96"}" INPUT_FILE/input.GAS
                ./run_phases.sh
                ./post_equilibrazione_md.sh
            else
                sed -i "8c ${b[0]}" INPUT_FILE/input.SOLID
                sed -i "9c ${b[1]}" INPUT_FILE/input.SOLID
                sed -i "1c ${j}" INPUT_FILE/input.SOLID
                sed -i "2c ${t}" INPUT_FILE/input.SOLID
                sed -i "3c ${"0.8"}" INPUT_FILE/input.SOLID
                sed -i "8c ${b[0]}" INPUT_FILE/input.LIQUID
                sed -i "9c ${b[1]}" INPUT_FILE/input.LIQUID
                sed -i "1c ${j}" INPUT_FILE/input.LIQUID
                sed -i "2c ${t}" INPUT_FILE/input.LIQUID
                sed -i "3c ${"1.1"}" INPUT_FILE/input.LIQUID
                sed -i "8c ${b[0]}" INPUT_FILE/input.GAS
                sed -i "9c ${b[1]}" INPUT_FILE/input.GAS
                sed -i "1c ${j}" INPUT_FILE/input.GAS
                sed -i "2c ${t}" INPUT_FILE/input.GAS
                sed -i "3c ${"1.2"}" INPUT_FILE/input.GAS
                ./run_phases.sh
            fi
        elif $t == 1; then
                sed -i "7c ${"0.1"}" INPUT_FILE/input.SOLID
                sed -i "8c ${a[0]}" INPUT_FILE/input.SOLID
                sed -i "9c ${a[1]}" INPUT_FILE/input.SOLID
                sed -i "1c ${j}" INPUT_FILE/input.SOLID
                sed -i "2c ${t}" INPUT_FILE/input.SOLID
                sed -i "3c ${"1.5"}" INPUT_FILE/input.SOLID
                sed -i "7c ${"0.5"}" INPUT_FILE/input.LIQUID
                sed -i "8c ${a[0]}" INPUT_FILE/input.LIQUID
                sed -i "9c ${a[1]}" INPUT_FILE/input.LIQUID
                sed -i "1c ${j}" INPUT_FILE/input.LIQUID
                sed -i "2c ${t}" INPUT_FILE/input.LIQUID
                sed -i "3c ${"2"}" INPUT_FILE/input.LIQUID
                sed -i "7c ${"5"}" INPUT_FILE/input.GAS
                sed -i "8c ${a[0]}" INPUT_FILE/input.GAS
                sed -i "9c ${a[1]}" INPUT_FILE/input.GAS
                sed -i "1c ${j}" INPUT_FILE/input.GAS
                sed -i "2c ${t}" INPUT_FILE/input.GAS
                sed -i "3c ${"0.96"}" INPUT_FILE/input.GAS
                ./run_phases.sh
                ./post_equilibrazione_mc.sh
        else
            sed -i "8c ${b[0]}" INPUT_FILE/input.SOLID
            sed -i "9c ${b[1]}" INPUT_FILE/input.SOLID
            sed -i "1c ${j}" INPUT_FILE/input.SOLID
            sed -i "2c ${t}" INPUT_FILE/input.SOLID
            sed -i "3c ${"0.80"}" INPUT_FILE/input.SOLID
            sed -i "8c ${b[0]}" INPUT_FILE/input.LIQUID
            sed -i "9c ${b[1]}" INPUT_FILE/input.LIQUID
            sed -i "1c ${j}" INPUT_FILE/input.LIQUID
            sed -i "2c ${t}" INPUT_FILE/input.LIQUID
            sed -i "3c ${"1.1"}" INPUT_FILE/input.LIQUID
            sed -i "8c ${b[0]}" INPUT_FILE/input.GAS
            sed -i "9c ${b[1]}" INPUT_FILE/input.GAS
            sed -i "1c ${j}" INPUT_FILE/input.GAS
            sed -i "2c ${t}" INPUT_FILE/input.GAS
            sed -i "3c ${"1.2"}" INPUT_FILE/input.GAS
            ./run_phases.sh
        fi
    done
done