.name		"Gopnik21"
.comment	"vasya ale"

sti		r1, %21, %2
sti		r1, %21, %1
sti		r1, %21, %2
sti		r1, %21, %1
sti		r1, %21, %2
sti		r1, %21, %1
sti		r1, %21, %2
sti		r1, %21, %1
sti		r1, %21, %2
sti		r1, %21, %1
sti		r1, %21, %2
sti		r1, %21, %1
ld		%21, r2
ld		%21, r1
fork	%1260


live	%42
st		r2, -21
st		r1, -42
st		r2, -63
st		r1, -84
st		r2, -105
st		r1, -126
st		r2, -147
st		r1, -168
st		r2, -189
st		r1, -210
st		r2, -231
st		r1, -252
st		r2, -273
st		r1, -294
st		r2, -315
st		r1, -336
st		r2, -357
st		r1, -378
st		r2, -399
st		r1, -420
st		r2, -840
st		r1, -1260

zjmp	%1260
