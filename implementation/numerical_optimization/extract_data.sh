# look them up in /tmp/temp.log

for number in {2..10}
do
    #ls -p | grep -v / | grep -e '^[a-Z]' | xargs grep -e '^the end' --color | grep -o '[0-9]\..*' > /tmp/temp.log
    ls -p | grep -v / | grep -e '^[0-9]' | xargs grep -e '^the end' --color > /tmp/temp.log
    echo "$number"
done

