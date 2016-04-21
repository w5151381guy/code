.data 
	question1:.asciiz "Please input the first integer: \0"
	question2:.asciiz "Please input the second integer: \0"
	ans:.asciiz "GCD is: \0"
.text
main:
	li $v0,4
	la $a0,question1           #cout<<question1
	syscall
	li $v0,5
	syscall
	move $t0,$v0               #move $v0->$t0
	li $v0,4
	la $a0,question2           #cout<<question2
	syscall
	li $v0,5
	syscall
	move $t1,$v0               #move $v0->$t1
	jal GCD

	move $t3,$v0               #put result into $t3
	li $v0,4
	la $a0,ans
	syscall


	li $v0,1
	move $a0,$t3
	syscall
	
	li $v0, 10
	syscall
	
GCD:
	addi $sp,$sp,-4
	sw $ra,0($sp)
	bnez $t1,L1                #if($1 != 0) jump L1
	add $v0,$zero,$t0          # if base case is true
	addi $sp,$sp,4
	jr $ra
L1:
	div $t0,$t1
	move $t0,$t1
	mfhi $t1
	jal GCD
	lw $ra,0($sp)
	addi $sp,$sp,4
	jr $ra
