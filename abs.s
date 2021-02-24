.name       "Batman"
.comment    "This city needs me"

loop:
        sti r1, %:live, %1    # <-- На эту операцию указывает метка loop
live:
        live %0               # <-- На эту операцию указывает метка live
        ld %0, r2             # <-- А на эту операцию никакая метка не указывает
        zjmp %:loop
