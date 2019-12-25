assume CS:code DS:data

data segment
    
    dw 0761H,0772H,0779H
    dw 0761H,076EH,0720H
    dw 076CH,076FH,0776H
    dw 0765H,0720H,0761H
    dw 0772H,0779H,0761H
    
data ends

code segment

start:
    mov AX,0B800H
    mov SS,AX
    
    mov AX,data
    mov DS,AX

    mov BX,0
    mov BP,0
    mov CX,15
s:  
    mov AX,[BX]
    mov [BP],AX
    add BX,2
    add BP,2
    loop s
    
    mov AX,4C00H
    int 21H
    
    
code ends

end start