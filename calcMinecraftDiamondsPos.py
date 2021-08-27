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


###################################################

# 方法原作者Matthew Bolan （from bilibili up 小包小包i）
# 视频的方法目前仅适用于java1.16 

#------------------------------#
# 河流中： 
# 1.粘土z+2（81.25%） 
# 2.砂砾z-2（75%） 
# 3.砂砾z+8（25%÷2） 

# 沼泽中（粘土和砂砾一致）： 
# 1.粘土z+7（87.25%） 
# 2.粘土z+0（12.5%） 
#------------------------------#

# （沼泽粘土找钻石的z+7其实是方便的找法） 
# 在距离6格出现的概率是37.5% 
# 距离8格出现的概率是50% 
# 然后由于钻石的生成方向通常在-z的方向 
# 作者认为在7的时候是比较好找的

###################################################
