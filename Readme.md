# README

## TODO

check if dir sorting is necessary in sort
clean more logic
norminette

## Bonuses

### Done

* perf mode
* error where they matter
* -1 ?

### Not done

* More options

## Testing code

``` bash
ls -1 > /tmp/b
ls -1 -R >> /tmp/b
ls -1 -Rarl >> /tmp/b
ls -1l . ~ o >> /tmp/b


./ft_ls > /tmp/a
./ft_ls -R >> /tmp/a
./ft_ls -Rarl >> /tmp/a
./ft_ls -l . ~ o >> /tmp/a

code -- diff /tmp/a /tmp/b

# ---

ls -1l . ~ o &> /tmp/b
./ft_ls -l . ~ o &> /tmp/a

code --diff /tmp/a /tmp/b

# ---

echo "ls" > /tmp/a
~/42/ls/ft_ls >> /tmp/a
echo "ls '.'" >> /tmp/a
~/42/ls/ft_ls '.' >> /tmp/a
echo "ls -l" >> /tmp/a
~/42/ls/ft_ls -l >> /tmp/a
echo "ls -l '.' " >> /tmp/a
~/42/ls/ft_ls -l '.'  >> /tmp/a
echo "ls '.' '.' " >> /tmp/a
~/42/ls/ft_ls '.' '.'  >> /tmp/a
echo "ls -l '.' '.' " >> /tmp/a
~/42/ls/ft_ls -l '.' '.'  >> /tmp/a

echo "ls -t" >> /tmp/a
~/42/ls/ft_ls -t >> /tmp/a
echo "ls -t '.'" >> /tmp/a
~/42/ls/ft_ls -t '.' >> /tmp/a
echo "ls -tl" >> /tmp/a
~/42/ls/ft_ls -tl >> /tmp/a
echo "ls -tl '.' " >> /tmp/a
~/42/ls/ft_ls -tl '.'  >> /tmp/a
echo "ls -t '.' '.' " >> /tmp/a
~/42/ls/ft_ls -t '.' '.'  >> /tmp/a
echo "ls -tl '.' '.' " >> /tmp/a
~/42/ls/ft_ls -tl '.' '.'  >> /tmp/a

echo "ls -r" >> /tmp/a
~/42/ls/ft_ls -r >> /tmp/a
echo "ls -r '.'" >> /tmp/a
~/42/ls/ft_ls -r '.' >> /tmp/a
echo "ls -lr" >> /tmp/a
~/42/ls/ft_ls -lr >> /tmp/a
echo "ls -lr '.' " >> /tmp/a
~/42/ls/ft_ls -lr '.'  >> /tmp/a
echo "ls -r '.' '.' " >> /tmp/a
~/42/ls/ft_ls -r '.' '.'  >> /tmp/a
echo "ls -lr '.' '.' " >> /tmp/a
~/42/ls/ft_ls -lr '.' '.'  >> /tmp/a

echo "ls -tr" >> /tmp/a
~/42/ls/ft_ls -tr >> /tmp/a
echo "ls -tr '.'" >> /tmp/a
~/42/ls/ft_ls -tr '.' >> /tmp/a
echo "ls -tlr" >> /tmp/a
~/42/ls/ft_ls -tlr >> /tmp/a
echo "ls -tlr '.' " >> /tmp/a
~/42/ls/ft_ls -tlr '.'  >> /tmp/a
echo "ls -tr '.' '.' " >> /tmp/a
~/42/ls/ft_ls -tr '.' '.'  >> /tmp/a
echo "ls -tlr '.' '.' " >> /tmp/a
~/42/ls/ft_ls -tlr '.' '.'  >> /tmp/a

echo "ls" > /tmp/b
ls >> /tmp/b
echo "ls '.'" >> /tmp/b
ls '.' >> /tmp/b
echo "ls -l" >> /tmp/b
ls -l >> /tmp/b
echo "ls -l '.' " >> /tmp/b
ls -l '.'  >> /tmp/b
echo "ls '.' '.' " >> /tmp/b
ls '.' '.'  >> /tmp/b
echo "ls -l '.' '.' " >> /tmp/b
ls -l '.' '.'  >> /tmp/b

echo "ls -t" >> /tmp/b
ls -t >> /tmp/b
echo "ls -t '.'" >> /tmp/b
ls -t '.' >> /tmp/b
echo "ls -tl" >> /tmp/b
ls -tl >> /tmp/b
echo "ls -tl '.' " >> /tmp/b
ls -tl '.'  >> /tmp/b
echo "ls -t '.' '.' " >> /tmp/b
ls -t '.' '.'  >> /tmp/b
echo "ls -tl '.' '.' " >> /tmp/b
ls -tl '.' '.'  >> /tmp/b

echo "ls -r" >> /tmp/b
ls -r >> /tmp/b
echo "ls -r '.'" >> /tmp/b
ls -r '.' >> /tmp/b
echo "ls -lr" >> /tmp/b
ls -lr >> /tmp/b
echo "ls -lr '.' " >> /tmp/b
ls -lr '.'  >> /tmp/b
echo "ls -r '.' '.' " >> /tmp/b
ls -r '.' '.'  >> /tmp/b
echo "ls -lr '.' '.' " >> /tmp/b
ls -lr '.' '.'  >> /tmp/b

echo "ls -tr" >> /tmp/b
ls -tr >> /tmp/b
echo "ls -tr '.'" >> /tmp/b
ls -tr '.' >> /tmp/b
echo "ls -tlr" >> /tmp/b
ls -tlr >> /tmp/b
echo "ls -tlr '.' " >> /tmp/b
ls -tlr '.'  >> /tmp/b
echo "ls -tr '.' '.' " >> /tmp/b
ls -tr '.' '.'  >> /tmp/b
echo "ls -tlr '.' '.' " >> /tmp/b
ls -tlr '.' '.'  >> /tmp/b

code --diff /tmp/a /tmp/b

# ---

echo "ls -Rtlr" > /tmp/a
~/42/ls/ft_ls -Rtlr >> /tmp/a 2>&1

echo "ls -Rtlr" > /tmp/b
ls -Rtlr >> /tmp/b 2>&1

code --diff /tmp/a /tmp/b

# ---

```
