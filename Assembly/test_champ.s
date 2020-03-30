.name       "Batman"
.comment    "This city needs me"

loop:
        sti r1, %:live, %1 #a comment!
live:
        live %0
        ld %0, r2
        zjmp %:loop
