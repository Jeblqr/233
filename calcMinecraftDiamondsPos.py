#idea from bilibili up 一只冰迷, uid = 489776897
#mol mol mol %%% 一只冰迷
#written by Jeblqr

mul = 25214903917
mask = (1 << 48) - 1
offset_116 = 60009
offset_117 = 60011

def getBlockPos():
    block_x = int(input('请输入区块坐标x：'))
    block_z = int(input('请输入区块坐标z：'))
    return block_x, block_z

def printDiamondPos(x, z):
    print('钻石的坐标：')
    print('x =', x)
    print('z =', z)

def getIJ(seed):
    temp = (seed ^ mul) & mask
    temp = (temp * mul + 11) & mask
    temp1 = temp >> 16 << 32
    temp = (temp * mul + 11) & mask
    temp2 = temp << 16 >> 32
    temp = (temp * mul + 11) & mask
    temp3 = temp >> 16 << 32
    temp = (temp * mul + 11) & mask
    temp4 = temp << 16 >> 32
    i = (temp1 + temp2) | 1 
    j = (temp3 + temp4) | 1
    return i, j

def getRelPos(block_x, block_z, seed, i, j, offset):
    block_k = ((16 * block_x * i + 16 * block_z * j) ^ seed) + offset
    block_k = block_k ^ mul & mask
    block_k = (block_k * mul + 11) & mask
    rel_x = block_k >> 44
    block_k = (block_k * mul + 11) & mask
    rel_z = block_k >> 44
    return rel_x, rel_z

def getAbsPos(block_x, block_z, rel_x, rel_z):
    x = rel_x + 16 * block_x
    z = rel_z + 16 * block_z
    return x, z

def getPos116(seed):
    block_x, block_z = getBlockPos()
    i, j = getIJ(seed)
    rel_x, rel_z = getRelPos(block_x, block_z, seed, i, j, offset_116)
    x, z = getAbsPos(block_x, block_z, rel_x, rel_z)
    printDiamondPos(x, z)

def getPos117(seed):
    block_x, block_z = getBlockPos()
    i, j = getIJ(seed)
    rel_x, rel_z = getRelPos(block_x, block_z, seed, i, j, offset_117)
    x, z = getAbsPos(block_x, block_z, rel_x, rel_z)
    printDiamondPos(x, z)

def getPos(version, seed):
    if version == 1:
        while True:
            getPos116(seed)
    else:
        while True:
            getPos117(seed)

def calc():
    print('[1] 1.16.x')
    print('[2] 1.17.x')
    version = int(input('请输入版本序号: '))
    seed = int(input('请输入地图种子：'))
    getPos(version, seed)


calc()
