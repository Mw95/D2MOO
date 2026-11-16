# Generates the synthetic game data used by D2LangDiffTests, in the directory given as argument (the working directory
# of the tests):
# - data/local/use: the string table language (English)
# - data/local/lng/ENG/{string,patchstring,expansionstring}.tbl: string tables, and keys.txt listing their keys
# - data/local/font/LATIN/default.map: the system code page map loaded with the string tables
# - test.map, bad.map: a valid and an invalid system code page map for the loadSysMap tests
import struct, os, random, sys
random.seed(1)
os.chdir(sys.argv[1] if len(sys.argv) > 1 else '.')

def crc16(data):
    tbl=[]
    for i in range(256):
        c=i<<8
        for _ in range(8): c=((c<<1)^0x1021) if c&0x8000 else (c<<1)
        tbl.append(c&0xFFFF)
    crc=0xFFFF
    for b in data: crc=(tbl[((crc>>8)^b)&0xFF]^(crc<<8))&0xFFFF
    return crc

def elf(key):
    h=0
    for ch in key:
        c=ch if ch<128 else ch-256
        h=((h<<4)+c)&0xFFFFFFFF
        hi=h&0xF0000000
        if hi: h=(h&0x0FFFFFFF)^(hi>>24)
    return h

def make_tbl(entries, hash_size):
    n=len(entries)
    header_size=21; nodes_off=header_size+2*n; data_off=nodes_off+17*hash_size
    nodes=[None]*hash_size; data=bytearray(); maxloops=0
    for i,(key,val) in enumerate(entries):
        kb=key.encode('latin1'); vb=val.encode('utf-8')
        koff=data_off+len(data); data+=kb+b'\0'
        voff=data_off+len(data); data+=vb+b'\0'
        h=elf(kb)%hash_size; loops=1
        while nodes[h] is not None: h=(h+1)%hash_size; loops+=1
        maxloops=max(maxloops,loops)
        nodes[h]=(1,i,elf(kb),koff,voff,len(vb)+1)
    idx=[0]*n
    for hpos,nd in enumerate(nodes):
        if nd: idx[nd[1]]=hpos
    body=b''.join(struct.pack('<H',x) for x in idx)
    for nd in nodes: body+=struct.pack('<BHIIIH',*(nd if nd else (0,0,0,0,0,0)))
    size=header_size+len(body)+len(data)
    hdr=struct.pack('<HHiBIII',0,n,hash_size,0,data_off,maxloops,size)
    blob=bytearray(hdr+body+data)
    struct.pack_into('<H',blob,0,crc16(blob[data_off:size]))
    return bytes(blob)

def strings(prefix,count,special={}):
    out=[]
    for i in range(count):
        if i in special: out.append(special[i]); continue
        key='%s%d'%(prefix,i)
        if random.random()<0.1: key=key.upper()
        val=random.choice(['%s value %d'%(prefix,i), 'Café %d'%i, 'あい %d'%i, '', 'x'*(i%40)])
        out.append((key,val))
    return out

base=strings('base',6000,{5328:('thousand','k'),5329:('million','Mio'),5330:('billion',''),5331:('trillion','T'),500:('fallback','Fallback string')})
patch=strings('patch',800,{3:('base10','Patched base10'),4:('shared','Patch shared')})
exp=strings('exp',700,{5:('base11','Expansion base11'),6:('shared','Expansion shared'),7:('patch20','Expansion patch20')})
os.makedirs('data/local/lng/ENG',exist_ok=True)
open('data/local/lng/ENG/string.tbl','wb').write(make_tbl(base,7919))
open('data/local/lng/ENG/patchstring.tbl','wb').write(make_tbl(patch,1201))
open('data/local/lng/ENG/expansionstring.tbl','wb').write(make_tbl(exp,1031))
# LATIN font map: every byte is a single-byte character mapped to itself
os.makedirs('data/local/font/LATIN',exist_ok=True)
m=b"KAMAP\nLatin\r\n\x1a\0\0\0\0"+struct.pack('<HB',0xE0,1)+bytes([0x20,0xFF])
m+=b''.join(struct.pack('<HH',c,c) for c in range(0x20,0x100))
m+=b''.join(struct.pack('<H',i) for i in range(0xE0))
open('data/local/font/LATIN/default.map','wb').write(m)
with open('keys.txt','w',encoding='latin1') as f:
    for k,_ in base+patch+exp: f.write(k+'\n')

# Synthetic KAMAP: single-byte ranges and a byte <-> Unicode mapping (the loader only keeps the low byte of each value)
random.seed(7)
ranges=[(0x20,0x7F),(0xA1,0xDF)]
sys_codes=[b for b in range(0x20,0x100) if b not in (0x40,0x9A)]
unis=list(range(0x20,0x100)); random.shuffle(unis); unis=unis[:len(sys_codes)]
entries=sorted(zip(sys_codes,unis), key=lambda e:e[1])
idx=sorted(range(len(entries)), key=lambda i:entries[i][0])
data=b"KAMAP\n"+b"TestMap\r\n"+b"\x1a"+b"\0\0\0\0"
data+=struct.pack('<HB',len(entries),len(ranges))
for a,b in ranges: data+=bytes([a,b])
for sc,u in entries: data+=struct.pack('<HH',sc|0x8100,u|0x3000)  # high bytes are ignored by the loader
for i in idx: data+=struct.pack('<H',i)
open('test.map','wb').write(data)
open('bad.map','wb').write(b"NOTAMAP\n"+b"\0"*64)

open('data/local/use','wb').write(b'\0')
