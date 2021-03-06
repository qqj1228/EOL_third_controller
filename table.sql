USE JAC
GO
-- 车辆信息表
IF OBJECT_ID(N'JAC.dbo.VehicleInfo') IS NOT NULL
    DROP TABLE JAC.dbo.VehicleInfo
GO
CREATE TABLE JAC.dbo.VehicleInfo
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
    VIN varchar(17) NOT NULL UNIQUE, -- VIN码
	VehicleType varchar(30) NOT NULL, -- 车型代码
)
GO

-- 插入字段备注
EXEC sp_addextendedproperty N'MS_Description', N'ID', N'USER', N'dbo', N'TABLE', N'VehicleInfo', N'COLUMN', N'ID'
EXEC sp_addextendedproperty N'MS_Description', N'VIN码', N'USER', N'dbo', N'TABLE', N'VehicleInfo', N'COLUMN', N'VIN'
EXEC sp_addextendedproperty N'MS_Description', N'车型代码', N'USER', N'dbo', N'TABLE', N'VehicleInfo', N'COLUMN', N'VehicleType'
GO

-- 测试: 插入数据
INSERT JAC.dbo.VehicleInfo (VIN, VehicleType)
    VALUES ('testvincode012345', 'IEV6')
GO
-- 测试: 修改数据
UPDATE JAC.dbo.VehicleInfo
    SET VehicleType = 'IEV6S'
    WHERE VIN = 'testvincode012345'
GO
-- 测试: 查询数据
SELECT VIN, VehicleType
    FROM JAC.dbo.VehicleInfo
GO

-- 定位仪配置信息表
IF OBJECT_ID(N'JAC.dbo.NCAConfig') IS NOT NULL
    DROP TABLE JAC.dbo.NCAConfig
GO
CREATE TABLE JAC.dbo.NCAConfig
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
    VehicleType varchar(30) NOT NULL UNIQUE, -- 车型代码
	VehicleID int NULL, -- 车型序号
	WheelBaseValue int NULL, -- 轴距
	TyreRadius int NULL, -- 轮胎半径
	HubRadius int NULL, -- 转毂半径
	RotatePeriodTime int NULL, -- 转动周期
	DriveRatio float NULL, -- 传动比
	RearAxleEnable int NULL, -- 是否调整后轴
	CasterEnable int NULL, -- 是否检测主销后倾
	TAEnable int NULL, -- 是否检测转角

	FT_Toe_Mid float NULL, -- 前轴前束和中值
	FT_Toe_Dev float NULL, -- 前轴前束和偏差
	FL_Toe_Mid float NULL, -- 前左轮前束中值
	FL_Toe_Dev float NULL, -- 前左轮前束偏差
	FR_Toe_Mid float NULL, -- 前右轮前束中值
	FR_Toe_Dev float NULL, -- 前右轮前束偏差
	FC_Camber_Mid float NULL, -- 前轴外倾差中值
	FC_Camber_Dev float NULL, -- 前轴外倾差偏差
	FL_Camber_Mid float NULL, -- 前左轮外倾中值
	FL_Camber_Dev float NULL, -- 前左轮外倾偏差
	FR_Camber_Mid float NULL, -- 前右轮外倾中值
	FR_Camber_Dev float NULL, -- 前右轮外倾偏差
	RT_Toe_Mid float NULL, -- 后轴前束和中值
	RT_Toe_Dev float NULL, -- 后轴前束和偏差
	RL_Toe_Mid float NULL, -- 后左轮前束中值
	RL_Toe_Dev float NULL, -- 后左轮前束偏差
	RR_Toe_Mid float NULL, -- 后右轮前束中值
	RR_Toe_Dev float NULL, -- 后右轮前束偏差
	RC_Camber_Mid float NULL, -- 后轴外倾差中值
	RC_Camber_Dev float NULL, -- 后轴外倾差偏差
	RL_Camber_Mid float NULL, -- 后左轮外倾中值
	RL_Camber_Dev float NULL, -- 后左轮外倾偏差
	RR_Camber_Mid float NULL, -- 后右轮外倾中值
	RR_Camber_Dev float NULL, -- 后右轮外倾偏差
	Thrust_Ang_Min float NULL, -- 推进角最小值
	Thrust_Ang_Max float NULL, -- 推进角最大值
	Symmetry_Min float NULL, -- 对称角最小值
	Symmetry_Max float NULL, -- 对称角最大值
	SWL_Angle_Min float NULL, -- 方向盘摆正器角度最小值
	SWL_Angle_Max float NULL, -- 方向盘摆正器角度最大值
	FL_Caster_Min float NULL, -- 前左轮主销后倾最小值
	FL_Caster_Max float NULL, -- 前左轮主销后倾最大值
	FR_Caster_Min float NULL, -- 前右轮主销后倾最小值
	FR_Caster_Max float NULL, -- 前右轮主销后倾最大值
	FC_Caster_Min float NULL, -- 主销后倾差最小值
	FC_Caster_Max float NULL, -- 主销后倾差最大值
	FL_TA_Inner_Min float NULL, -- 前左轮Inner转角最小值/前左轮转角左转最小值
	FL_TA_Inner_Max float NULL, -- 前左轮Inner转角最大值/前左轮转角左转最大值
	FL_TA_Outer_Min float NULL, -- 前左轮Outer转角最小值/前左轮转角右转最小值
	FL_TA_Outer_Max float NULL, -- 前左轮Outer转角最大值/前左轮转角右转最大值
	FR_TA_Inner_Min float NULL, -- 前右轮Inner转角最小值/前右轮转角右转最小值
	FR_TA_Inner_Max float NULL, -- 前右轮Inner转角最大值/前右轮转角右转最大值
	FR_TA_Outer_Min float NULL, -- 前右轮Outer转角最小值/前右轮转角左转最小值
	FR_TA_Outer_Max float NULL, -- 前右轮Outer转角最大值/前右轮转角左转最大值
)
GO

EXEC sp_addextendedproperty N'MS_Description', 'ID', N'user', N'dbo', N'table', N'NCAConfig', N'column', N'ID'
EXEC sp_addextendedproperty N'MS_Description', '车型代码', N'user', N'dbo', N'table', N'NCAConfig', N'column', N'VehicleType'
EXEC sp_addextendedproperty N'MS_Description', '车型序号', N'user', N'dbo', N'table', N'NCAConfig', N'column', N'VehicleID'
EXEC sp_addextendedproperty N'MS_Description', '轴距', N'user', N'dbo', N'table', N'NCAConfig', N'column', N'WheelBaseValue'
EXEC sp_addextendedproperty N'MS_Description', '轮胎半径', N'user', N'dbo', N'table', N'NCAConfig', N'column', N'TyreRadius'
EXEC sp_addextendedproperty N'MS_Description', '转毂半径', N'user', N'dbo', N'table', N'NCAConfig', N'column', N'HubRadius'
EXEC sp_addextendedproperty N'MS_Description', '转动周期', N'user', N'dbo', N'table', N'NCAConfig', N'column', N'RotatePeriodTime'
EXEC sp_addextendedproperty N'MS_Description', '传动比', N'user', N'dbo', N'table', N'NCAConfig', N'column', N'DriveRatio'
EXEC sp_addextendedproperty N'MS_Description', '是否调整后轴', N'user', N'dbo', N'table', N'NCAConfig', N'column', N'RearAxleEnable'
EXEC sp_addextendedproperty N'MS_Description', '是否检测主销后倾', N'user', N'dbo', N'table', N'NCAConfig', N'column', N'CasterEnable'
EXEC sp_addextendedproperty N'MS_Description', '是否检测转角', N'user', N'dbo', N'table', N'NCAConfig', N'column', N'TAEnable'

EXEC sp_addextendedproperty N'MS_Description', '前轴前束和中值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FT_Toe_Mid'
EXEC sp_addextendedproperty N'MS_Description', '前轴前束和偏差', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FT_Toe_Dev'
EXEC sp_addextendedproperty N'MS_Description', '前左轮前束中值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FL_Toe_Mid'
EXEC sp_addextendedproperty N'MS_Description', '前左轮前束偏差', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FL_Toe_Dev'
EXEC sp_addextendedproperty N'MS_Description', '前右轮前束中值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FR_Toe_Mid'
EXEC sp_addextendedproperty N'MS_Description', '前右轮前束偏差', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FR_Toe_Dev'
EXEC sp_addextendedproperty N'MS_Description', '前轴外倾差中值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FC_Camber_Mid'
EXEC sp_addextendedproperty N'MS_Description', '前轴外倾差偏差', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FC_Camber_Dev'
EXEC sp_addextendedproperty N'MS_Description', '前左轮外倾中值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FL_Camber_Mid '
EXEC sp_addextendedproperty N'MS_Description', '前左轮外倾偏差', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FL_Camber_Dev'
EXEC sp_addextendedproperty N'MS_Description', '前右轮外倾中值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FR_Camber_Mid'
EXEC sp_addextendedproperty N'MS_Description', '前右轮外倾偏差', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FR_Camber_Dev'
EXEC sp_addextendedproperty N'MS_Description', '后轴前束和中值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'RT_Toe_Mid'
EXEC sp_addextendedproperty N'MS_Description', '后轴前束和偏差', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'RT_Toe_Dev'
EXEC sp_addextendedproperty N'MS_Description', '后左轮前束中值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'RL_Toe_Mid'
EXEC sp_addextendedproperty N'MS_Description', '后左轮前束偏差', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'RL_Toe_Dev'
EXEC sp_addextendedproperty N'MS_Description', '后右轮前束中值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'RR_Toe_Mid'
EXEC sp_addextendedproperty N'MS_Description', '后右轮前束偏差', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'RR_Toe_Dev'
EXEC sp_addextendedproperty N'MS_Description', '后轴外倾差中值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'RC_Camber_Mid' 
EXEC sp_addextendedproperty N'MS_Description', '后轴外倾差偏差', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'RC_Camber_Dev'
EXEC sp_addextendedproperty N'MS_Description', '后左轮外倾中值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'RL_Camber_Mid'
EXEC sp_addextendedproperty N'MS_Description', '后左轮外倾偏差', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'RL_Camber_Dev'
EXEC sp_addextendedproperty N'MS_Description', '后右轮外倾中值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'RR_Camber_Mid'
EXEC sp_addextendedproperty N'MS_Description', '后右轮外倾偏差', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'RR_Camber_Dev'
EXEC sp_addextendedproperty N'MS_Description', '推进角最小值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'Thrust_Ang_Min'
EXEC sp_addextendedproperty N'MS_Description', '推进角最大值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'Thrust_Ang_Max'
EXEC sp_addextendedproperty N'MS_Description', '对称角最小值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'Symmetry_Min'
EXEC sp_addextendedproperty N'MS_Description', '对称角最大值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'Symmetry_Max'
EXEC sp_addextendedproperty N'MS_Description', '方向盘摆正器角度最小值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'SWL_Angle_Min'
EXEC sp_addextendedproperty N'MS_Description', '方向盘摆正器角度最大值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'SWL_Angle_Max'
EXEC sp_addextendedproperty N'MS_Description', '前左轮主销后倾最小值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FL_Caster_Min'
EXEC sp_addextendedproperty N'MS_Description', '前左轮主销后倾最大值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FL_Caster_Max'
EXEC sp_addextendedproperty N'MS_Description', '前右轮主销后倾最小值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FR_Caster_Min'
EXEC sp_addextendedproperty N'MS_Description', '前右轮主销后倾最大值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FR_Caster_Max'
EXEC sp_addextendedproperty N'MS_Description', '主销后倾差最小值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FC_Caster_Min'
EXEC sp_addextendedproperty N'MS_Description', '主销后倾差最大值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FC_Caster_Max'
EXEC sp_addextendedproperty N'MS_Description', '前左轮Inner转角最小值/前左轮转角左转最小值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FL_TA_Inner_Min'
EXEC sp_addextendedproperty N'MS_Description', '前左轮Inner转角最大值/前左轮转角左转最大值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FL_TA_Inner_Max'
EXEC sp_addextendedproperty N'MS_Description', '前左轮Outer转角最小值/前左轮转角右转最小值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FL_TA_Outer_Min'
EXEC sp_addextendedproperty N'MS_Description', '前左轮Outer转角最大值/前左轮转角右转最大值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FL_TA_Outer_Max'
EXEC sp_addextendedproperty N'MS_Description', '前右轮Inner转角最小值/前右轮转角右转最小值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FR_TA_Inner_Min'
EXEC sp_addextendedproperty N'MS_Description', '前右轮Inner转角最大值/前右轮转角右转最大值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FR_TA_Inner_Max'
EXEC sp_addextendedproperty N'MS_Description', '前右轮Outer转角最小值/前右轮转角左转最小值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FR_TA_Outer_Min'
EXEC sp_addextendedproperty N'MS_Description', '前右轮Outer转角最大值/前右轮转角左转最大值', N'user', N'dbo', N'table', N'NCAConfig', N'column', 'FR_TA_Outer_Max'
GO

-- 测试: 插入数据
INSERT JAC.dbo.NCAConfig
    VALUES (
        'IEV6S',
		10,
		2490,
		600,
		500,
		1000,
		3.2,
		1,
		1,
		1,
		0.16,
		0.08,
		0.16,
		0.08,
		0.16,
		0.08,
		0.16,
		0.08,
		0.16,
		0.08,
		0.16,
		0.08,
		0.16,
		0.08,
		0.16,
		0.08,
		0.16,
		0.08,
		0.16,
		0.08,
		0.16,
		0.08,
		0.16,
		0.08,
		0.02,
		0.08,
		0.02,
		0.08,
		0.02,
		0.08,
		0.02,
		0.08,
		0.02,
		0.08,
		0.02,
		0.08,
		0.02,
		0.08,
		0.02,
		0.08,
		0.02,
		0.08,
		0.02,
		0.08
    )
GO

-- 测试: 查询数据
SELECT *
    FROM JAC.dbo.NCAConfig
GO

-- 灯光仪配置信息表
IF OBJECT_ID(N'JAC.dbo.HLAConfig') IS NOT NULL
    DROP TABLE JAC.dbo.HLAConfig
GO
CREATE TABLE JAC.dbo.HLAConfig
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
	VehicleType varchar(30) NOT NULL UNIQUE, -- 车型代码
	VehicleID int NULL, -- 车型序号
	LowBeamAdjustEnable int NULL, -- 是否调整近光灯位置
	HighBeamAdjustEnable int NULL, -- 是否调整远光灯位置
	FogBeamAdjustEnable int NULL, -- 是否调整雾灯位置
	FogBeamTestEnable int NULL, -- 是否检测雾灯
	AutoLBtoHBEnable int NULL, -- 是否自动切换远近光
	LowHeight int NULL, -- 车型参数 - 近光灯高度
	LowDistance int NULL, -- 车型参数 - 近光灯间距
	HighHeight int NULL, -- 车型参数 - 远光灯高度
	HighDistance int NULL, -- 车型参数 - 远光灯间距
	FogHeight int NULL, -- 车型参数 - 雾灯高度
	FogDistance int NULL, -- 车型参数 - 雾灯间距

	LowInten_Min float NULL, -- 合格范围 - 近光光强最小值
	LowInten_Max float NULL, -- 合格范围 - 近光光强最大值
	LowHor_Mid float NULL, -- 合格范围 - 近光水平偏移中值
	LowHor_Dev float NULL, -- 合格范围 - 近光水平偏移偏差
	LowVer_Mid float NULL, -- 合格范围 - 近光垂直偏移中值
	LowVer_Dev float NULL, -- 合格范围 - 近光垂直偏移偏差
	HighInten_Min float NULL, -- 合格范围 - 远光光强最小值
	HighInten_Max float NULL, -- 合格范围 - 远光光强最大值
	HighHor_Mid float NULL, -- 合格范围 - 远光水平偏移中值
	HighHor_Dev float NULL, -- 合格范围 - 远光水平偏移偏差
	HighVer_Mid float NULL, -- 合格范围 - 远光垂直偏移中值
	HighVer_Dev float NULL, -- 合格范围 - 远光垂直偏移偏差
	FogInten_Min float NULL, -- 合格范围 - 雾灯光强最小值
	FogInten_Max float NULL, -- 合格范围 - 雾灯光强最大值
	FogHor_Mid float NULL, -- 合格范围 - 雾灯水平偏移中值
	FogHor_Dev float NULL, -- 合格范围 - 雾灯水平偏移偏差
	FogVer_Mid float NULL, -- 合格范围 - 雾灯垂直偏移中值
	FogVer_Dev float NULL, -- 合格范围 - 雾灯垂直偏移偏差
)
GO

-- 插入字段备注
EXEC sp_addextendedproperty N'MS_Description', 'ID', N'user', N'dbo', N'table', N'HLAConfig', N'column', N'ID'
EXEC sp_addextendedproperty N'MS_Description', '车型代码', N'user', N'dbo', N'table', N'HLAConfig', N'column', N'VehicleType'
EXEC sp_addextendedproperty N'MS_Description', '车型序号', N'user', N'dbo', N'table', N'HLAConfig', N'column', N'VehicleID'
EXEC sp_addextendedproperty N'MS_Description', '是否调整近光灯位置', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'LowBeamAdjustEnable'
EXEC sp_addextendedproperty N'MS_Description', '是否调整远光灯位置', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'HighBeamAdjustEnable'
EXEC sp_addextendedproperty N'MS_Description', '是否调整雾灯位置', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'FogBeamAdjustEnable'
EXEC sp_addextendedproperty N'MS_Description', '是否检测雾灯', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'FogBeamTestEnable'
EXEC sp_addextendedproperty N'MS_Description', '是否自动切换远近光', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'AutoLBtoHBEnable'
EXEC sp_addextendedproperty N'MS_Description', '近光灯高度', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'LowHeight'
EXEC sp_addextendedproperty N'MS_Description', '近光灯间距', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'LowDistance'
EXEC sp_addextendedproperty N'MS_Description', '远光灯高度', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'HighHeight'
EXEC sp_addextendedproperty N'MS_Description', '远光灯间距', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'HighDistance'
EXEC sp_addextendedproperty N'MS_Description', '雾灯高度', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'FogHeight'
EXEC sp_addextendedproperty N'MS_Description', '雾灯间距', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'FogDistance'

EXEC sp_addextendedproperty N'MS_Description', '近光光强最小值', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'LowInten_Min'
EXEC sp_addextendedproperty N'MS_Description', '近光光强最大值', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'LowInten_Max'
EXEC sp_addextendedproperty N'MS_Description', '近光水平偏移中值', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'LowHor_Mid'
EXEC sp_addextendedproperty N'MS_Description', '近光水平偏移偏差', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'LowHor_Dev'
EXEC sp_addextendedproperty N'MS_Description', '近光垂直偏移中值', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'LowVer_Mid'
EXEC sp_addextendedproperty N'MS_Description', '近光垂直偏移偏差', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'LowVer_Dev'
EXEC sp_addextendedproperty N'MS_Description', '远光光强最小值', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'HighInten_Min'
EXEC sp_addextendedproperty N'MS_Description', '远光光强最大值', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'HighInten_Max'
EXEC sp_addextendedproperty N'MS_Description', '远光水平偏移中值', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'HighHor_Mid'
EXEC sp_addextendedproperty N'MS_Description', '远光水平偏移偏差', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'HighHor_Dev'
EXEC sp_addextendedproperty N'MS_Description', '远光垂直偏移中值', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'HighVer_Mid'
EXEC sp_addextendedproperty N'MS_Description', '远光垂直偏移偏差', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'HighVer_Dev'
EXEC sp_addextendedproperty N'MS_Description', '雾灯光强最小值', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'FogInten_Min'
EXEC sp_addextendedproperty N'MS_Description', '雾灯光强最大值', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'FogInten_Max'
EXEC sp_addextendedproperty N'MS_Description', '雾灯水平偏移中值', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'FogHor_Mid'
EXEC sp_addextendedproperty N'MS_Description', '雾灯水平偏移偏差', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'FogHor_Dev'
EXEC sp_addextendedproperty N'MS_Description', '雾灯垂直偏移中值', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'FogVer_Mid'
EXEC sp_addextendedproperty N'MS_Description', '雾灯垂直偏移偏差', N'user', N'dbo', N'table', N'HLAConfig', N'column', 'FogVer_Dev'
GO

-- 测试: 插入数据
INSERT JAC.dbo.HLAConfig
    VALUES (
		'IEV6S',
		10,
		1,
		1,
		1,
		1,
		1,
		1000,
		1500,
		1050,
		1500,
		1200,
		1600,
		1000.2,
		1000.8,
		800.5,
		80,
		800.5,
		80,
		1000.2,
		1000.8,
		800.5,
		80,
		800.5,
		80,
		1000.2,
		1000.8,
		800.5,
		80,
		800.5,
		80
	)
GO

-- 测试: 查询数据
SELECT *
    FROM JAC.dbo.HLAConfig
GO

-- 侧滑台配置信息表
IF OBJECT_ID(N'JAC.dbo.SideSlipConfig') IS NOT NULL
    DROP TABLE JAC.dbo.SideSlipConfig
GO
CREATE TABLE JAC.dbo.SideSlipConfig
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
	VehicleType varchar(30) NOT NULL UNIQUE, -- 车型代码
)
GO

-- 插入字段备注
EXEC sp_addextendedproperty N'MS_Description', 'ID', N'user', N'dbo', N'table', N'SideSlipConfig', N'column', N'ID'
EXEC sp_addextendedproperty N'MS_Description', '车型代码', N'user', N'dbo', N'table', N'SideSlipConfig', N'column', N'VehicleType'
GO

-- 测试: 插入数据
INSERT JAC.dbo.SideSlipConfig (VehicleType)
    VALUES ('IEV6S')
GO
-- 测试: 查询数据
SELECT *
    FROM JAC.dbo.SideSlipConfig
GO

-- 制动台配置信息表
IF OBJECT_ID(N'JAC.dbo.BrakeConfig') IS NOT NULL
    DROP TABLE JAC.dbo.BrakeConfig
GO
CREATE TABLE JAC.dbo.BrakeConfig
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
	VehicleType varchar(30) NOT NULL UNIQUE, -- 车型代码
	WheelBaseValue int NULL, -- 轴距
)
GO

-- 插入字段备注
EXEC sp_addextendedproperty N'MS_Description', 'ID', N'user', N'dbo', N'table', N'BrakeConfig', N'column', N'ID'
EXEC sp_addextendedproperty N'MS_Description', '车型代码', N'user', N'dbo', N'table', N'BrakeConfig', N'column', N'VehicleType'
EXEC sp_addextendedproperty N'MS_Description', '轴距', N'user', N'dbo', N'table', N'BrakeConfig', N'column', N'WheelBaseValue'
GO

-- 测试: 插入数据
INSERT JAC.dbo.BrakeConfig (VehicleType, WheelBaseValue)
    VALUES ('IEV6S', 2490)
GO
-- 测试: 查询数据
SELECT *
    FROM JAC.dbo.BrakeConfig
GO

---------------------------------------------------------------
------------------------ 测试结果数据表 ------------------------
---------------------------------------------------------------

-- 定位仪前束外倾测试结果表
IF OBJECT_ID(N'JAC.dbo.NCAToeCamberResult') IS NOT NULL
    DROP TABLE JAC.dbo.NCAToeCamberResult
GO
CREATE TABLE JAC.dbo.NCAToeCamberResult
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
	VIN varchar(17) NOT NULL, -- VIN码
	InspectDate DATE NULL, -- 检测日期
	InspectTime TIME NULL, -- 检测时间
	VehicleType varchar(30) NOT NULL, -- 车型代码
	CycleTime int NULL, -- 循环时间
	Result char(1) NULL, -- 总评, O是合格, X是不合格

	FT_Toe float NULL, -- 前轴前束和数值
	FT_Toe_Result char(1) NULL, -- 前轴前束和评判, O是合格, X是不合格
	FL_Toe float NULL, -- 前左轮前束数值
	FL_Toe_Result char(1) NULL, -- 前左轮前束评判
	FR_Toe float NULL, -- 前右轮前束数值
	FR_Toe_Result char(1) NULL, -- 前右轮前束评判
	FC_Camber float NULL, -- 前轴外倾差数值
	FC_Camber_Result char(1) NULL, -- 前轴外倾差评判
	FL_Camber float NULL, -- 前左轮外倾数值
	FL_Camber_Result char(1) NULL, -- 前左轮外倾评判
	FR_Camber float NULL, -- 前右轮外倾数值
	FR_Camber_Result char(1) NULL, -- 前右轮外倾评判
	RT_Toe float NULL, -- 后轴前束和数值
	RT_Toe_Result char(1) NULL, -- 后轴前束和评判
	RL_Toe float NULL, -- 后左轮前束数值
	RL_Toe_Result char(1) NULL, -- 后左轮前束评判
	RR_Toe float NULL, -- 后右轮前束数值
	RR_Toe_Result char(1) NULL, -- 后右轮前束评判
	RC_Camber float NULL, -- 后轴外倾差数值
	RC_Camber_Result char(1) NULL, -- 后轴外倾差评判
	RL_Camber float NULL, -- 后左轮外倾数值
	RL_Camber_Result char(1) NULL, -- 后左轮外倾评判
	RR_Camber float NULL, -- 后右轮外倾数值
	RR_Camber_Result char(1) NULL, -- 后右轮外倾评判
	Thrust_Ang float NULL, -- 推进角数值
	Thrust_Ang_Result char(1) NULL, -- 推进角评判
	Symmetry float NULL, -- 对称角数值
	Symmetry_Result char(1) NULL, -- 对称角评判
	SWL_Angle float NULL, -- 方向盘摆正器角度数值
	SWL_Angle_Result char(1) NULL, -- 方向盘摆正器角度评判
)
GO

-- 插入字段备注
EXEC sp_addextendedproperty N'MS_Description', 'ID', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', N'ID'
EXEC sp_addextendedproperty N'MS_Description', 'VIN码', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', N'VIN'
EXEC sp_addextendedproperty N'MS_Description', '检测日期', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', N'InspectDate'
EXEC sp_addextendedproperty N'MS_Description', '检测时间', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', N'InspectTime'
EXEC sp_addextendedproperty N'MS_Description', '车型代码', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', N'VehicleType'
EXEC sp_addextendedproperty N'MS_Description', '循环时间', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', N'CycleTime'
EXEC sp_addextendedproperty N'MS_Description', '总评', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', N'Result'

EXEC sp_addextendedproperty N'MS_Description', '前轴前束和数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'FT_Toe'
EXEC sp_addextendedproperty N'MS_Description', '前轴前束和评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'FT_Toe_Result'
EXEC sp_addextendedproperty N'MS_Description', '前左轮前束数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'FL_Toe'
EXEC sp_addextendedproperty N'MS_Description', '前左轮前束评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'FL_Toe_Result'
EXEC sp_addextendedproperty N'MS_Description', '前右轮前束数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'FR_Toe'
EXEC sp_addextendedproperty N'MS_Description', '前右轮前束评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'FR_Toe_Result'
EXEC sp_addextendedproperty N'MS_Description', '前轴外倾差数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'FC_Camber'
EXEC sp_addextendedproperty N'MS_Description', '前轴外倾差评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'FC_Camber_Result'
EXEC sp_addextendedproperty N'MS_Description', '前左轮外倾数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'FL_Camber'
EXEC sp_addextendedproperty N'MS_Description', '前左轮外倾评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'FL_Camber_Result'
EXEC sp_addextendedproperty N'MS_Description', '前右轮外倾数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'FR_Camber'
EXEC sp_addextendedproperty N'MS_Description', '前右轮外倾评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'FR_Camber_Result'
EXEC sp_addextendedproperty N'MS_Description', '后轴前束和数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'RT_Toe'
EXEC sp_addextendedproperty N'MS_Description', '后轴前束和评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'RT_Toe_Result'
EXEC sp_addextendedproperty N'MS_Description', '后左轮前束数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'RL_Toe'
EXEC sp_addextendedproperty N'MS_Description', '后左轮前束评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'RL_Toe_Result'
EXEC sp_addextendedproperty N'MS_Description', '后右轮前束数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'RR_Toe'
EXEC sp_addextendedproperty N'MS_Description', '后右轮前束评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'RR_Toe_Result'
EXEC sp_addextendedproperty N'MS_Description', '后轴外倾差数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'RC_Camber'
EXEC sp_addextendedproperty N'MS_Description', '后轴外倾差评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'RC_Camber_Result'
EXEC sp_addextendedproperty N'MS_Description', '后左轮外倾数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'RL_Camber'
EXEC sp_addextendedproperty N'MS_Description', '后左轮外倾评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'RL_Camber_Result'
EXEC sp_addextendedproperty N'MS_Description', '后右轮外倾数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'RR_Camber'
EXEC sp_addextendedproperty N'MS_Description', '后右轮外倾评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'RR_Camber_Result'
EXEC sp_addextendedproperty N'MS_Description', '推进角数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'Thrust_Ang'
EXEC sp_addextendedproperty N'MS_Description', '推进角评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'Thrust_Ang_Result'
EXEC sp_addextendedproperty N'MS_Description', '对称角数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'Symmetry'
EXEC sp_addextendedproperty N'MS_Description', '对称角评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'Symmetry_Result'
EXEC sp_addextendedproperty N'MS_Description', '方向盘摆正器角度数值', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'SWL_Angle'
EXEC sp_addextendedproperty N'MS_Description', '方向盘摆正器角度评判', N'user', N'dbo', N'table', N'NCAToeCamberResult', N'column', 'SWL_Angle_Result'
GO

-- 测试: 插入数据
INSERT JAC.dbo.NCAToeCamberResult
    VALUES (
		'testvincode012345',
		'2013-03-17',
		'10:41:08',
		'IEV6S',
		232,
		'O',
		0.07,
		'O',
		0.12,
		'O',
		0.10,
		'O',
		-0.16,
		'O',
		-0.39,
		'O',
		-0.23,
		'O',
		0.14,
		'O',
		0.15,
		'O',
		-0.01,
		'O',
		0.25,
		'O',
		-1.27,
		'O',
		-1.52,
		'O',
		0.08,
		'O',
		-0.06,
		'O',
		0.1,
		'O'
	)
GO
-- 测试: 查询数据
SELECT *
    FROM JAC.dbo.NCAToeCamberResult
GO

-- 定位仪主销后倾测试结果表
IF OBJECT_ID(N'JAC.dbo.NCACasterResult') IS NOT NULL
    DROP TABLE JAC.dbo.NCACasterResult
GO
CREATE TABLE JAC.dbo.NCACasterResult
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
	VIN varchar(17) NOT NULL, -- VIN码
	InspectDate DATE NULL, -- 检测日期
	InspectTime TIME NULL, -- 检测时间
	VehicleType varchar(30) NOT NULL, -- 车型代码
	CycleTime int NULL, -- 循环时间
	Caster_Result char(1) NULL, -- 主销后倾总评, O是合格, X是不合格

	FL_Caster float NULL, -- 前左轮主销后倾数值
	FL_Caster_Result char(1) NULL, -- 前左轮主销后倾评判
	FR_Caster float NULL, -- 前右轮主销后倾数值
	FR_Caster_Result char(1) NULL, -- 前右轮主销后倾评判
	FC_Caster float NULL, -- 主销后倾差数值
	FC_Caster_Result char(1) NULL, -- 主销后倾差评判
)
GO

-- 插入字段备注
EXEC sp_addextendedproperty N'MS_Description', 'ID', N'user', N'dbo', N'table', N'NCACasterResult', N'column', N'ID'
EXEC sp_addextendedproperty N'MS_Description', 'VIN码', N'user', N'dbo', N'table', N'NCACasterResult', N'column', N'VIN'
EXEC sp_addextendedproperty N'MS_Description', '检测日期', N'user', N'dbo', N'table', N'NCACasterResult', N'column', N'InspectDate'
EXEC sp_addextendedproperty N'MS_Description', '检测时间', N'user', N'dbo', N'table', N'NCACasterResult', N'column', N'InspectTime'
EXEC sp_addextendedproperty N'MS_Description', '车型代码', N'user', N'dbo', N'table', N'NCACasterResult', N'column', N'VehicleType'
EXEC sp_addextendedproperty N'MS_Description', '循环时间', N'user', N'dbo', N'table', N'NCACasterResult', N'column', N'CycleTime'
EXEC sp_addextendedproperty N'MS_Description', '主销后倾总评', N'user', N'dbo', N'table', N'NCACasterResult', N'column', N'Caster_Result'

EXEC sp_addextendedproperty N'MS_Description', '前左轮主销后倾数值', N'user', N'dbo', N'table', N'NCACasterResult', N'column', N'FL_Caster'
EXEC sp_addextendedproperty N'MS_Description', '前左轮主销后倾评判', N'user', N'dbo', N'table', N'NCACasterResult', N'column', N'FL_Caster_Result'
EXEC sp_addextendedproperty N'MS_Description', '前右轮主销后倾数值', N'user', N'dbo', N'table', N'NCACasterResult', N'column', N'FR_Caster'
EXEC sp_addextendedproperty N'MS_Description', '前右轮主销后倾评判', N'user', N'dbo', N'table', N'NCACasterResult', N'column', N'FR_Caster_Result'
EXEC sp_addextendedproperty N'MS_Description', '主销后倾差数值', N'user', N'dbo', N'table', N'NCACasterResult', N'column', N'FC_Caster'
EXEC sp_addextendedproperty N'MS_Description', '主销后倾差评判', N'user', N'dbo', N'table', N'NCACasterResult', N'column', N'FC_Caster_Result'
GO

-- 测试: 插入数据
INSERT JAC.dbo.NCACasterResult
    VALUES (
		'testvincode012345',
		'2013-03-17',
		'10:41:08',
		'IEV6S',
		232,
		'O',
		3.2,
		'O',
		3.2,
		'O',
		3.2,
		'O'
	)
GO
-- 测试: 查询数据
SELECT *
    FROM JAC.dbo.NCACasterResult
GO

-- 定位仪最大转角测试结果表
IF OBJECT_ID(N'JAC.dbo.NCATurningAngleResult') IS NOT NULL
    DROP TABLE JAC.dbo.NCATurningAngleResult
GO
CREATE TABLE JAC.dbo.NCATurningAngleResult
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
	VIN varchar(17) NOT NULL, -- VIN码
	InspectDate DATE NULL, -- 检测日期
	InspectTime TIME NULL, -- 检测时间
	VehicleType varchar(30) NOT NULL, -- 车型代码
	CycleTime int NULL, -- 循环时间
	TA_Result char(1) NULL, -- 最大转角总评, O是合格, X是不合格

	FL_TA_Inner float NULL, -- 前左轮转角左转数值
	FL_TA_Inner_Result char(1) NULL, -- 前左轮转角左转评判
	FL_TA_Outer float NULL, -- 前左轮转角右转数值
	FL_TA_Outer_Result char(1) NULL, -- 前左轮转角右转评判
	FR_TA_Inner float NULL, -- 前右轮转角右转数值
	FR_TA_Inner_Result char(1) NULL, -- 前右轮转角右转评判
	FR_TA_Outer float NULL, -- 前右轮转角左转数值
	FR_TA_Outer_Result char(1) NULL, -- 前右轮转角左转评判
)
GO

-- 插入字段备注
EXEC sp_addextendedproperty N'MS_Description', 'ID', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'ID'
EXEC sp_addextendedproperty N'MS_Description', 'VIN码', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'VIN'
EXEC sp_addextendedproperty N'MS_Description', '检测日期', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'InspectDate'
EXEC sp_addextendedproperty N'MS_Description', '检测时间', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'InspectTime'
EXEC sp_addextendedproperty N'MS_Description', '车型代码', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'VehicleType'
EXEC sp_addextendedproperty N'MS_Description', '循环时间', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'CycleTime'
EXEC sp_addextendedproperty N'MS_Description', '最大转角总评', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'TA_Result'

EXEC sp_addextendedproperty N'MS_Description', '前左轮转角左转数值', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'FL_TA_Inner'
EXEC sp_addextendedproperty N'MS_Description', '前左轮转角左转评判', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'FL_TA_Inner_Result'
EXEC sp_addextendedproperty N'MS_Description', '前左轮转角右转数值', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'FL_TA_Outer'
EXEC sp_addextendedproperty N'MS_Description', '前左轮转角右转评判', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'FL_TA_Outer_Result'
EXEC sp_addextendedproperty N'MS_Description', '前右轮转角右转数值', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'FR_TA_Inner'
EXEC sp_addextendedproperty N'MS_Description', '前右轮转角右转评判', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'FR_TA_Inner_Result'
EXEC sp_addextendedproperty N'MS_Description', '前右轮转角左转数值', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'FR_TA_Outer'
EXEC sp_addextendedproperty N'MS_Description', '前右轮转角左转评判', N'user', N'dbo', N'table', N'NCATurningAngleResult', N'column', N'FR_TA_Outer_Result'
GO

-- 测试: 插入数据
INSERT JAC.dbo.NCATurningAngleResult
    VALUES (
		'testvincode012345',
		'2013-03-17',
		'10:41:08',
		'IEV6S',
		232,
		'O',
		-34.3,
		'O',
		34.3,
		'O',
		34.3,
		'O',
		-34.3,
		'O'
	)
GO
-- 测试: 查询数据
SELECT *
    FROM JAC.dbo.NCATurningAngleResult
GO

-- 灯光仪测试结果表
IF OBJECT_ID(N'JAC.dbo.HLAResult') IS NOT NULL
    DROP TABLE JAC.dbo.HLAResult
GO
CREATE TABLE JAC.dbo.HLAResult
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
	VIN varchar(17) NOT NULL, -- VIN码
	InspectDate DATE NULL, -- 检测日期
	InspectTime TIME NULL, -- 检测时间
	CycleTime int NULL, -- 循环时间
	TotalResult char(1) NULL, -- 灯光总评, O是合格, X是不合格

	LLowInten float NULL, -- 左灯近光光强数值, O是合格, X是不合格
	LLowInten_Result char(1) NULL, -- 左灯近光光强评判
	LLowHor float NULL, -- 左灯近光水平偏移数值
	LLowHor_Result char(1) NULL, -- 左灯近光水平偏移评判
	LLowVer float NULL, -- 左灯近光垂直偏移数值
	LLowVer_Result char(1) NULL, -- 左灯近光垂直偏移评判
	LHighInten float NULL, -- 左灯远光光强数值
	LHighInten_Result char(1) NULL, -- 左灯远光光强评判
	LHighHor float NULL, -- 左灯远光水平偏移数值
	LHighHor_Result char(1) NULL, -- 左灯远光水平偏移评判
	LHighVer float NULL, -- 左灯远光垂直偏移数值
	LHighVer_Result char(1) NULL, -- 左灯远光垂直偏移评判
	RLowInten float NULL, -- 右灯近光光强数值
	RLowInten_Result char(1) NULL, -- 右灯近光光强评判
	RLowHor float NULL, -- 右灯近光水平偏移数值
	RLowHor_Result char(1) NULL, -- 右灯近光水平偏移评判
	RLowVer float NULL, -- 右灯近光垂直偏移数值
	RLowVer_Result char(1) NULL, -- 右灯近光垂直偏移评判
	RHighInten float NULL, -- 右灯远光光强数值
	RHighInten_Result char(1) NULL, -- 右灯远光光强评判
	RHighHor float NULL, -- 右灯远光水平偏移数值
	RHighHor_Result char(1) NULL, -- 右灯远光水平偏移评判
	RHighVer float NULL, -- 右灯远光垂直偏移数值
	RHighVer_Result char(1) NULL, -- 右灯远光垂直偏移评判
)
GO

-- 插入字段备注
EXEC sp_addextendedproperty N'MS_Description', 'ID', N'user', N'dbo', N'table', N'HLAResult', N'column', N'ID'
EXEC sp_addextendedproperty N'MS_Description', 'VIN码', N'user', N'dbo', N'table', N'HLAResult', N'column', N'VIN'
EXEC sp_addextendedproperty N'MS_Description', '检测日期', N'user', N'dbo', N'table', N'HLAResult', N'column', N'InspectDate'
EXEC sp_addextendedproperty N'MS_Description', '检测时间', N'user', N'dbo', N'table', N'HLAResult', N'column', N'InspectTime'
EXEC sp_addextendedproperty N'MS_Description', '循环时间', N'user', N'dbo', N'table', N'HLAResult', N'column', N'CycleTime'
EXEC sp_addextendedproperty N'MS_Description', '灯光总评', N'user', N'dbo', N'table', N'HLAResult', N'column', N'TotalResult'

EXEC sp_addextendedproperty N'MS_Description', '左灯近光光强数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LLowInten'
EXEC sp_addextendedproperty N'MS_Description', '左灯近光光强评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LLowInten_Result'
EXEC sp_addextendedproperty N'MS_Description', '左灯近光水平偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LLowHor'
EXEC sp_addextendedproperty N'MS_Description', '左灯近光水平偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LLowHor_Result'
EXEC sp_addextendedproperty N'MS_Description', '左灯近光垂直偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LLowVer'
EXEC sp_addextendedproperty N'MS_Description', '左灯近光垂直偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LLowVer_Result'
EXEC sp_addextendedproperty N'MS_Description', '左灯远光光强数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LHighInten'
EXEC sp_addextendedproperty N'MS_Description', '左灯远光光强评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LHighInten_Result'
EXEC sp_addextendedproperty N'MS_Description', '左灯远光水平偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LHighHor'
EXEC sp_addextendedproperty N'MS_Description', '左灯远光水平偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LHighHor_Result'
EXEC sp_addextendedproperty N'MS_Description', '左灯远光垂直偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LHighVer'
EXEC sp_addextendedproperty N'MS_Description', '左灯远光垂直偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LHighVer_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯近光光强数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RLowInten'
EXEC sp_addextendedproperty N'MS_Description', '右灯近光光强评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RLowInten_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯近光水平偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RLowHor'
EXEC sp_addextendedproperty N'MS_Description', '右灯近光水平偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RLowHor_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯近光垂直偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RLowVer'
EXEC sp_addextendedproperty N'MS_Description', '右灯近光垂直偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RLowVer_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯远光光强数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RHighInten'
EXEC sp_addextendedproperty N'MS_Description', '右灯远光光强评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RHighInten_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯远光水平偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RHighHor'
EXEC sp_addextendedproperty N'MS_Description', '右灯远光水平偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RHighHor_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯远光垂直偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RHighVer'
EXEC sp_addextendedproperty N'MS_Description', '右灯远光垂直偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RHighVer_Result'
GO

-- 测试: 插入数据
INSERT JAC.dbo.HLAResult
    VALUES (
		'testvincode012345',
		'2013-03-17',
		'10:41:08',
		232,
		'O',
		13000.00,
		'O',
		0.61,
		'O',
		-0.22,
		'O',
		42000.00,
		'O',
		-13.97,
		'O',
		3.06,
		'O',
		13000.00,
		'O',
		-2.63,
		'O',
		0.36,
		'O',
		35000.00,
		'O',
		3.83,
		'O',
		9.78,
		'O'
	)
GO
-- 测试: 查询数据
SELECT *
    FROM JAC.dbo.HLAResult
GO

-- 侧滑台最大转角测试结果表
IF OBJECT_ID(N'JAC.dbo.SideSlipResult') IS NOT NULL
    DROP TABLE JAC.dbo.SideSlipResult
GO
CREATE TABLE JAC.dbo.SideSlipResult
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
	VIN varchar(17) NOT NULL, -- VIN码
	InspectDate DATE NULL, -- 检测日期
	InspectTime TIME NULL, -- 检测时间
	VehicleType varchar(30) NOT NULL, -- 车型代码
	CycleTime int NULL, -- 循环时间
	SlipResult char(1) NULL, -- 侧滑总评, O是合格, X是不合格

	FrontSlipValue float NULL, -- 前轴侧滑数值
	FrontSlipResult char(1) NULL, -- 前轴侧滑评判
	PassSpeed float NULL, -- 通过速度数值
	PassSpeedResult char(1) NULL, -- 通过速度评判
)
GO

-- 插入字段备注
EXEC sp_addextendedproperty N'MS_Description', 'ID', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'ID'
EXEC sp_addextendedproperty N'MS_Description', 'VIN码', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'VIN'
EXEC sp_addextendedproperty N'MS_Description', '检测日期', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'InspectDate'
EXEC sp_addextendedproperty N'MS_Description', '检测时间', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'InspectTime'
EXEC sp_addextendedproperty N'MS_Description', '车型代码', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'VehicleType'
EXEC sp_addextendedproperty N'MS_Description', '循环时间', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'CycleTime'
EXEC sp_addextendedproperty N'MS_Description', '侧滑总评', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'SlipResult'

EXEC sp_addextendedproperty N'MS_Description', '前轴侧滑数值', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'FrontSlipValue'
EXEC sp_addextendedproperty N'MS_Description', '前轴侧滑评判', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'FrontSlipResult'
EXEC sp_addextendedproperty N'MS_Description', '通过速度数值', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'PassSpeed'
EXEC sp_addextendedproperty N'MS_Description', '通过速度评判', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'PassSpeedResult'
GO

-- 测试: 插入数据
INSERT JAC.dbo.SideSlipResult
    VALUES (
		'testvincode012345',
		'2013-03-17',
		'10:41:08',
		'IEV6S',
		232,
		'O',
		0.0,
		'O',
		3.4,
		'O'
	)
GO
-- 测试: 查询数据
SELECT *
    FROM JAC.dbo.SideSlipResult
GO

-- 制动台最大转角测试结果表
IF OBJECT_ID(N'JAC.dbo.BrakeResult') IS NOT NULL
    DROP TABLE JAC.dbo.BrakeResult
GO
CREATE TABLE JAC.dbo.BrakeResult
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
	VIN varchar(17) NOT NULL, -- VIN码
	InspectDate DATE NULL, -- 检测日期
	InspectTime TIME NULL, -- 检测时间
	VehicleType varchar(30) NOT NULL, -- 车型代码
	CycleTime int NULL, -- 循环时间
	TotalResult char(1) NULL, -- 制动总评, O是合格, X是不合格

	FLWeightValue int NULL, -- 前左轮轮重数据
	FRWeightValue int NULL, -- 前右轮轮重数据
	RLWeightValue int NULL, -- 后左轮轮重数据
	RRWeightValue int NULL, -- 后右轮轮重数据
	FLBrakeMaxSumForce float NULL, -- 前轴最大制动和时左轮的制动力
	FRBraketMaxSumForce float NULL, -- 前轴最大制动和时右轮的制动力
	FLBrakeMaxDiffForce float NULL, -- 前轴最大制动差时左轮的制动力
	FRBrakeMaxDiffForce float NULL, -- 前轴最大制动差时右轮的制动力
	FrontBrakeMaxForce float NULL, -- 前轴制动过程中的最大制动力
	FLMaxDragForce float NULL, -- 前左轮最大阻滞力数值
	FRMaxDragForce float NULL, -- 前右轮最大阻滞力数值
	FrontMaxSumValue float NULL, -- 前轴最大制动和数值
	FrontMaxDiffValue float NULL, -- 前轴最大制动差数值
	FLDragValue float NULL, -- 前左轮阻滞率数值
	FRDragValue float NULL, -- 前右轮阻滞率数值
	FrontMaxSumResult char(1) NULL, -- 前轴最大制动和评判，O为合格，X为不合格
	FrontMaxDiffResult char(1) NULL, -- 前轴最大制动差评判
	FLDragResult char(1) NULL, -- 前左轮阻滞率评判
	FRDragResult char(1) NULL, -- 前右轮阻滞率评判
	RLBrakeMaxSumForce float NULL, -- 后轴最大制动和时左轮的制动力数值
	RRBrakeMaxSumForce float NULL, -- 后轴最大制动和时右轮的制动力数值
	RLBrakeMaxDiffForce float NULL, -- 后轴最大制动差时左轮的制动力数值
	RRBrakeMaxDiffForce float NULL, -- 后轴最大制动差时右轮的制动力数值
	RearBrakeMaxForce float NULL, -- 后轴制动过程中的最大制动力
	RLMaxDragForce float NULL, -- 后左轮最大阻滞力数值
	RRMaxDragForce float NULL, -- 后右轮最大阻滞力数值
	RearMaxSumValue float NULL, -- 后轴最大制动和数值
	RearMaxDiffValue float NULL, -- 后轴最大制动差数值
	RLMaxDragValue float NULL, -- 后左轮阻滞率数值
	RRMaxDragValue float NULL, -- 后右轮阻滞率数值
	RearMaxSumResult char(1) NULL, -- 后轴制动和评判
	RearMaxDiffResult char(1) NULL, -- 后轴制动差评判
	RLMaxDragResult char(1) NULL, -- 后左轮阻滞率评判
	RRMaxDragResult char(1) NULL, -- 后右轮阻滞率评判
	LeftParkMaxSumForce float NULL, -- 最大驻车和时的左轮制动力数值
	RightParkMaxSumForce float NULL, -- 最大驻车和时的右轮制动力数值
	ParkMaxSumValue float NULL, -- 驻车制动和数值
	ParkMaxSumResult char(1) NULL, -- 驻车制动和评判
	TotalSumValue float NULL, -- 整车制动和数值
	TotalSumResult char(1) NULL, -- 整车制动和评判
	PedalValue float NULL, -- 踏板力数值
	PedalResult char(1) NULL, -- 踏板力评判
	DragParkValue float NULL, -- 手拉力数值
	DragParkResult char(1) NULL, -- 手拉力评判
	FrontResponseTime float NULL, -- 前轴制动协调时间数值
	FrontRTResult char(1) NULL, -- 前轴制动协调时间评判
	RearResponseTime float NULL, -- 后轴制动协调时间数值
	RearRTResult char(1) NULL, -- 后轴制动协调时间评判
)
GO

-- 插入字段备注
EXEC sp_addextendedproperty N'MS_Description', 'ID', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'ID'
EXEC sp_addextendedproperty N'MS_Description', 'VIN码', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'VIN'
EXEC sp_addextendedproperty N'MS_Description', '检测日期', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'InspectDate'
EXEC sp_addextendedproperty N'MS_Description', '检测时间', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'InspectTime'
EXEC sp_addextendedproperty N'MS_Description', '车型代码', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'VehicleType'
EXEC sp_addextendedproperty N'MS_Description', '循环时间', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'CycleTime'
EXEC sp_addextendedproperty N'MS_Description', '制动总评', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'TotalResult'

EXEC sp_addextendedproperty N'MS_Description', '前左轮轮重数据', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FLWeightValue'
EXEC sp_addextendedproperty N'MS_Description', '前右轮轮重数据', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FRWeightValue'
EXEC sp_addextendedproperty N'MS_Description', '后左轮轮重数据', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RLWeightValue'
EXEC sp_addextendedproperty N'MS_Description', '后右轮轮重数据', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RRWeightValue'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动和时左轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FLBrakeMaxSumForce'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动和时右轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FRBraketMaxSumForce'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动差时左轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FLBrakeMaxDiffForce'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动差时右轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FRBrakeMaxDiffForce'
EXEC sp_addextendedproperty N'MS_Description', '前轴制动过程中的最大制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FrontBrakeMaxForce'
EXEC sp_addextendedproperty N'MS_Description', '前左轮最大阻滞力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FLMaxDragForce'
EXEC sp_addextendedproperty N'MS_Description', '前右轮最大阻滞力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FRMaxDragForce'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动和数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FrontMaxSumValue'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动差数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FrontMaxDiffValue'
EXEC sp_addextendedproperty N'MS_Description', '前左轮阻滞率数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FLDragValue'
EXEC sp_addextendedproperty N'MS_Description', '前右轮阻滞率数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FRDragValue'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动和评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FrontMaxSumResult'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动差评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FrontMaxDiffResult'
EXEC sp_addextendedproperty N'MS_Description', '前左轮阻滞率评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FLDragResult'
EXEC sp_addextendedproperty N'MS_Description', '前右轮阻滞率评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FRDragResult'
EXEC sp_addextendedproperty N'MS_Description', '后轴最大制动和时左轮的制动力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RLBrakeMaxSumForce'
EXEC sp_addextendedproperty N'MS_Description', '后轴最大制动和时右轮的制动力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RRBrakeMaxSumForce'
EXEC sp_addextendedproperty N'MS_Description', '后轴最大制动差时左轮的制动力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RLBrakeMaxDiffForce'
EXEC sp_addextendedproperty N'MS_Description', '后轴最大制动差时右轮的制动力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RRBrakeMaxDiffForce'
EXEC sp_addextendedproperty N'MS_Description', '后轴制动过程中的最大制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RearBrakeMaxForce'
EXEC sp_addextendedproperty N'MS_Description', '后左轮最大阻滞力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RLMaxDragForce'
EXEC sp_addextendedproperty N'MS_Description', '后右轮最大阻滞力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RRMaxDragForce'
EXEC sp_addextendedproperty N'MS_Description', '后轴最大制动和数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RearMaxSumValue'
EXEC sp_addextendedproperty N'MS_Description', '后轴最大制动差数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RearMaxDiffValue'
EXEC sp_addextendedproperty N'MS_Description', '后左轮阻滞率数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RLMaxDragValue'
EXEC sp_addextendedproperty N'MS_Description', '后右轮阻滞率数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RRMaxDragValue'
EXEC sp_addextendedproperty N'MS_Description', '后轴制动和评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RearMaxSumResult'
EXEC sp_addextendedproperty N'MS_Description', '后轴制动差评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RearMaxDiffResult'
EXEC sp_addextendedproperty N'MS_Description', '后左轮阻滞率评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RLMaxDragResult'
EXEC sp_addextendedproperty N'MS_Description', '后右轮阻滞率评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RRMaxDragResult'
EXEC sp_addextendedproperty N'MS_Description', '最大驻车和时的左轮制动力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'LeftParkMaxSumForce'
EXEC sp_addextendedproperty N'MS_Description', '最大驻车和时的右轮制动力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RightParkMaxSumForce'
EXEC sp_addextendedproperty N'MS_Description', '驻车制动和数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'ParkMaxSumValue'
EXEC sp_addextendedproperty N'MS_Description', '驻车制动和评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'ParkMaxSumResult'
EXEC sp_addextendedproperty N'MS_Description', '整车制动和数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'TotalSumValue'
EXEC sp_addextendedproperty N'MS_Description', '整车制动和评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'TotalSumResult'
EXEC sp_addextendedproperty N'MS_Description', '踏板力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'PedalValue'
EXEC sp_addextendedproperty N'MS_Description', '踏板力评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'PedalResult'
EXEC sp_addextendedproperty N'MS_Description', '手拉力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'DragParkValue'
EXEC sp_addextendedproperty N'MS_Description', '手拉力评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'DragParkResult'
EXEC sp_addextendedproperty N'MS_Description', '前轴制动协调时间数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FrontResponseTime'
EXEC sp_addextendedproperty N'MS_Description', '前轴制动协调时间评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FrontRTResult'
EXEC sp_addextendedproperty N'MS_Description', '后轴制动协调时间数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RearResponseTime'
EXEC sp_addextendedproperty N'MS_Description', '后轴制动协调时间评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RearRTResult'
GO

-- 测试: 插入数据
INSERT JAC.dbo.BrakeResult
    VALUES (
		'testvincode012345',
		'2013-03-17',
		'10:41:08',
		'IEV6S',
		74,
		'O',
		478,
		453,
		478,
		453,
		372,
		415,
		149,
		166,
		420,
		14,
		14,
		84.5,
		4.1,
		1.5,
		1.5,
		'O',
		'O',
		'O',
		'O',
		137,
		236,
		196,
		172,
		420,
		8,
		9,
		62.0,
		10.2,
		1.5,
		1.5,
		'O',
		'O',
		'O',
		'O',
		230,
		128,
		23.4,
		'O',
		75.7,
		'O',
		212,
		'O',
		189,
		'X',
		0.11,
		'O',
		0.15,
		'O'
	)
GO
-- 测试: 查询数据
SELECT *
    FROM JAC.dbo.BrakeResult
GO
