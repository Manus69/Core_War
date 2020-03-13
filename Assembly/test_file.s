.name       "Batman"
.comment    ""

p32:	sti	r7,%-510,r11
	add	r6,r6,r11
	ldi	%:p32deb,r6,r7
	