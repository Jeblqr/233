#idea from bilibili up 一只冰迷, uid = 489776897

mul = 25214903917
mask = (1 << 48) - 1

def GetIJ(seed):
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

def GetRelPos(block_x, block_z, seed, i, j):
    block_k = ((16 * block_x * i + 16 * block_z * j) ^ seed) + 60009
    block_k = block_k ^ mul & mask
    block_k = (block_k * mul + 11) & mask
    rel_x = block_k >> 44
    block_k = (block_k * mul + 11) & mask
    rel_z = block_k >> 44
    return rel_x, rel_z

def GetAbsPos(block_x, block_z, rel_x, rel_z):
    x = rel_x + 16 * block_x
    z = rel_z + 16 * block_z
    return x, z

def GetPos(seed):
    block_x = int(input('请输入区块坐标x：'))
    block_z = int(input('请输入区块坐标z：'))
    i, j = GetIJ(seed)
    rel_x, rel_z = GetRelPos(block_x, block_z, seed, i, j)
    x, z = GetAbsPos(block_x, block_z, rel_x, rel_z)
    print('钻石的坐标：')
    print('x =', x)
    print('z =', z)

seed = int(input('请输入地图种子：'))
while True:
    GetPos(seed)