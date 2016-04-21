.data 
	question:.asciiz  "Please input a integer: \0"
	sum:.word 0
	i:.word 1
	ans:.asciiz "Sum from one to input is: \0"
.text
main:
	li $v0,4
	la $a0,question      #cout<<question
	syscall
	li $v0,5
	syscall
	move $t0,$v0          #move $v0->$t0
	lw $t1,sum
	lw $t2,i
loop:
	add $t1,$t1,$t2       #sum += i
	beq $t0,$t2,print     #if(i == input)
	addi $t2,$t2,1        #i += 1
	j loop
print:
	li $v0,4
	la $a0,ans             #cout<<ans
	syscall
	li $v0,1
	move $a0,$t1
	syscall
