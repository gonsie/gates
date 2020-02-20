# Move to data directory before running
# run command:
# fish dataloader.fish ../../purger/Generated mcu

if test (count $argv) -ne 3
    echo "fish dataloader.fish purger-gen-path module-name"
end

for i in $argv
    echo $i
end

echo Processing component $argv[2]

set mcount 0
set offset 0
sort -n $argv[1]/$argv[2]/$argv[2].vSyn.gates > data-$mcount.vbench
#awk '{print NR-1 " " $0}' $argv[1]/$argv[2]/$argv[2].vSyn.gates > data-$mcount.vbench
echo Linked $argv[2].vSyn.gates to data-$mcount.vbench

set mcount (math $mcount + 1)
set offset (math $offset + (cat $argv[1]/$argv[2]/$argv[2].metadata))

for i in (cat $argv[1]/$argv[2]/$argv[2].clist)
    set -l _data (string split ' ' $i)
    for j in (seq 0 (math $_data[1] - 1))
        sort -n $argv[1]/$_data[2]/$_data[2].vSyn.gates.$j > data-$mcount.vbench
        #awk '{print NR-1 " " $0}' $argv[1]/$_data[2]/$_data[2].vSyn.gates.$j > data-$mcount.vbench
        echo Linked $_data[2].vSyn.gates.$j to data-$mcount.vbench offset $offset
        set mcount (math $mcount +1)
        set offset (math $offset + (cat $argv[1]/$_data[2]/$_data[2].metadata))
    end
end
