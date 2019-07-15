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

----------------------------------------------------------------
------------------------ 测试结果数据表 -------------------------
----------------------------------------------------------------

-- 定位仪测试结果表
IF OBJECT_ID(N'JAC.dbo.NCAResult') IS NOT NULL
    DROP TABLE JAC.dbo.NCAResult
GO
CREATE TABLE JAC.dbo.NCAResult
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
	VIN varchar(17) NOT NULL, -- VIN码
	VSN varchar(30) NULL, -- VSN码
	DateTime DATETIME NULL, -- 检测日期时间
	VehicleType varchar(30) NOT NULL, -- 车型代码

	FL_Toe float NULL, -- 前左轮前束数值
	FL_Toe_Result char(1) NULL, -- 前左轮前束评判, O是合格, X是不合格
	FR_Toe float NULL, -- 前右轮前束数值
	FR_Toe_Result char(1) NULL, -- 前右轮前束评判, O是合格, X是不合格
	FT_Toe float NULL, -- 前轴前束和数值
	FT_Toe_Result char(1) NULL, -- 前轴前束和评判, O是合格, X是不合格
	RL_Toe float NULL, -- 后左轮前束数值
	RL_Toe_Result char(1) NULL, -- 后左轮前束评判, O是合格, X是不合格
	RR_Toe float NULL, -- 后右轮前束数值
	RR_Toe_Result char(1) NULL, -- 后右轮前束评判, O是合格, X是不合格
	RT_Toe float NULL, -- 后轴前束和数值
	RT_Toe_Result char(1) NULL, -- 后轴前束和评判, O是合格, X是不合格
	FL_Camber float NULL, -- 前左轮外倾数值
	FL_Camber_Result char(1) NULL, -- 前左轮外倾评判, O是合格, X是不合格
	FR_Camber float NULL, -- 前右轮外倾数值
	FR_Camber_Result char(1) NULL, -- 前右轮外倾评判, O是合格, X是不合格
	FC_Camber float NULL, -- 前轴外倾差数值
	FC_Camber_Result char(1) NULL, -- 前轴外倾差评判, O是合格, X是不合格
	RL_Camber float NULL, -- 后左轮外倾数值
	RL_Camber_Result char(1) NULL, -- 后左轮外倾评判, O是合格, X是不合格
	RR_Camber float NULL, -- 后右轮外倾数值
	RR_Camber_Result char(1) NULL, -- 后右轮外倾评判, O是合格, X是不合格
	RC_Camber float NULL, -- 后轴外倾差数值
	RC_Camber_Result char(1) NULL, -- 后轴外倾差评判, O是合格, X是不合格
	Thrust_Ang float NULL, -- 推进角数值
	Thrust_Ang_Result char(1) NULL, -- 推进角评判, O是合格, X是不合格
	Symmetry float NULL, -- 对称角数值
	Symmetry_Result char(1) NULL, -- 对称角评判, O是合格, X是不合格
	SteelWheelAngle float NULL, -- 方向盘摆正器角度数值
	SteelWheelAngle_Result char(1) NULL, -- 方向盘摆正器角度评判, O是合格, X是不合格

	FL_Caster float NULL, -- 前左轮主销后倾数值
	FL_Caster_Result char(1) NULL, -- 前左轮主销后倾评判, O是合格, X是不合格
	FR_Caster float NULL, -- 前右轮主销后倾数值
	FR_Caster_Result char(1) NULL, -- 前右轮主销后倾评判, O是合格, X是不合格
	FC_Caster float NULL, -- 前轴主销后倾差数值
	FC_Caster_Result char(1) NULL, -- 前轴主销后倾差评判, O是合格, X是不合格
	FLSAI float NULL, -- 前左轮主销内倾数值
	FLSAI_Result char(1) NULL, -- 前左轮主销内倾评判, O是合格, X是不合格
	FRSAI float NULL, -- 前右轮主销内倾数值
	FRSAI_Result char(1) NULL, -- 前右轮主销内倾评判, O是合格, X是不合格

	LTAI float NULL, -- 左轮转角左转数值
	LTAI_Result char(1) NULL, -- 左轮转角左转评判, O是合格, X是不合格
	LTAO float NULL, -- 左轮转角右转数值
	LTAO_Result char(1) NULL, -- 左轮转角右转评判, O是合格, X是不合格
	RTAI float NULL, -- 右轮转角右转数值
	RTAI_Result char(1) NULL, -- 右轮转角右转评判, O是合格, X是不合格
	RTAO float NULL, -- 右轮转角左转数值
	RTAO_Result char(1) NULL, -- 右轮转角左转评判, O是合格, X是不合格
	Result char(1) NULL, -- 总评, O是合格, X是不合格
)
GO

-- 插入字段备注
EXEC sp_addextendedproperty N'MS_Description', 'ID', N'user', N'dbo', N'table', N'NCAResult', N'column', N'ID'
EXEC sp_addextendedproperty N'MS_Description', 'VIN码', N'user', N'dbo', N'table', N'NCAResult', N'column', N'VIN'
EXEC sp_addextendedproperty N'MS_Description', 'VSN码', N'user', N'dbo', N'table', N'NCAResult', N'column', N'VSN'
EXEC sp_addextendedproperty N'MS_Description', '检测日期时间', N'user', N'dbo', N'table', N'NCAResult', N'column', N'DateTime'
EXEC sp_addextendedproperty N'MS_Description', '车型代码', N'user', N'dbo', N'table', N'NCAResult', N'column', N'VehicleType'

EXEC sp_addextendedproperty N'MS_Description', '前左轮前束数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'FL_Toe'
EXEC sp_addextendedproperty N'MS_Description', '前左轮前束评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'FL_Toe_Result'
EXEC sp_addextendedproperty N'MS_Description', '前右轮前束数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'FR_Toe'
EXEC sp_addextendedproperty N'MS_Description', '前右轮前束评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'FR_Toe_Result'
EXEC sp_addextendedproperty N'MS_Description', '前轴前束和数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'FT_Toe'
EXEC sp_addextendedproperty N'MS_Description', '前轴前束和评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'FT_Toe_Result'
EXEC sp_addextendedproperty N'MS_Description', '后左轮前束数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'RL_Toe'
EXEC sp_addextendedproperty N'MS_Description', '后左轮前束评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'RL_Toe_Result'
EXEC sp_addextendedproperty N'MS_Description', '后右轮前束数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'RR_Toe'
EXEC sp_addextendedproperty N'MS_Description', '后右轮前束评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'RR_Toe_Result'
EXEC sp_addextendedproperty N'MS_Description', '后轴前束和数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'RT_Toe'
EXEC sp_addextendedproperty N'MS_Description', '后轴前束和评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'RT_Toe_Result'
EXEC sp_addextendedproperty N'MS_Description', '前左轮外倾数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'FL_Camber'
EXEC sp_addextendedproperty N'MS_Description', '前左轮外倾评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'FL_Camber_Result'
EXEC sp_addextendedproperty N'MS_Description', '前右轮外倾数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'FR_Camber'
EXEC sp_addextendedproperty N'MS_Description', '前右轮外倾评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'FR_Camber_Result'
EXEC sp_addextendedproperty N'MS_Description', '前轴外倾差数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'FC_Camber'
EXEC sp_addextendedproperty N'MS_Description', '前轴外倾差评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'FC_Camber_Result'
EXEC sp_addextendedproperty N'MS_Description', '后左轮外倾数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'RL_Camber'
EXEC sp_addextendedproperty N'MS_Description', '后左轮外倾评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'RL_Camber_Result'
EXEC sp_addextendedproperty N'MS_Description', '后右轮外倾数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'RR_Camber'
EXEC sp_addextendedproperty N'MS_Description', '后右轮外倾评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'RR_Camber_Result'
EXEC sp_addextendedproperty N'MS_Description', '后轴外倾差数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'RC_Camber'
EXEC sp_addextendedproperty N'MS_Description', '后轴外倾差评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'RC_Camber_Result'
EXEC sp_addextendedproperty N'MS_Description', '推进角数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'Thrust_Ang'
EXEC sp_addextendedproperty N'MS_Description', '推进角评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'Thrust_Ang_Result'
EXEC sp_addextendedproperty N'MS_Description', '对称角数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'Symmetry'
EXEC sp_addextendedproperty N'MS_Description', '对称角评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'Symmetry_Result'
EXEC sp_addextendedproperty N'MS_Description', '方向盘摆正器角度数值', N'user', N'dbo', N'table', N'NCAResult', N'column', 'SteelWheelAngle'
EXEC sp_addextendedproperty N'MS_Description', '方向盘摆正器角度评判', N'user', N'dbo', N'table', N'NCAResult', N'column', 'SteelWheelAngle_Result'

EXEC sp_addextendedproperty N'MS_Description', '前左轮主销后倾数值', N'user', N'dbo', N'table', N'NCAResult', N'column', N'FL_Caster'
EXEC sp_addextendedproperty N'MS_Description', '前左轮主销后倾评判', N'user', N'dbo', N'table', N'NCAResult', N'column', N'FL_Caster_Result'
EXEC sp_addextendedproperty N'MS_Description', '前右轮主销后倾数值', N'user', N'dbo', N'table', N'NCAResult', N'column', N'FR_Caster'
EXEC sp_addextendedproperty N'MS_Description', '前右轮主销后倾评判', N'user', N'dbo', N'table', N'NCAResult', N'column', N'FR_Caster_Result'
EXEC sp_addextendedproperty N'MS_Description', '前轴主销后倾数值', N'user', N'dbo', N'table', N'NCAResult', N'column', N'FC_Caster'
EXEC sp_addextendedproperty N'MS_Description', '前轴主销后倾评判', N'user', N'dbo', N'table', N'NCAResult', N'column', N'FC_Caster_Result'
EXEC sp_addextendedproperty N'MS_Description', '前左轮主销内倾数值', N'user', N'dbo', N'table', N'NCAResult', N'column', N'FLSAI'
EXEC sp_addextendedproperty N'MS_Description', '前左轮主销内倾评判', N'user', N'dbo', N'table', N'NCAResult', N'column', N'FLSAI_Result'
EXEC sp_addextendedproperty N'MS_Description', '前右轮主销内倾数值', N'user', N'dbo', N'table', N'NCAResult', N'column', N'FRSAI'
EXEC sp_addextendedproperty N'MS_Description', '前右轮主销内倾评判', N'user', N'dbo', N'table', N'NCAResult', N'column', N'FRSAI_Result'

EXEC sp_addextendedproperty N'MS_Description', '前左轮转角左转数值', N'user', N'dbo', N'table', N'NCAResult', N'column', N'LTAI'
EXEC sp_addextendedproperty N'MS_Description', '前左轮转角左转评判', N'user', N'dbo', N'table', N'NCAResult', N'column', N'LTAI_Result'
EXEC sp_addextendedproperty N'MS_Description', '前左轮转角右转数值', N'user', N'dbo', N'table', N'NCAResult', N'column', N'LTAO'
EXEC sp_addextendedproperty N'MS_Description', '前左轮转角右转评判', N'user', N'dbo', N'table', N'NCAResult', N'column', N'LTAO_Result'
EXEC sp_addextendedproperty N'MS_Description', '前右轮转角右转数值', N'user', N'dbo', N'table', N'NCAResult', N'column', N'RTAI'
EXEC sp_addextendedproperty N'MS_Description', '前右轮转角右转评判', N'user', N'dbo', N'table', N'NCAResult', N'column', N'RTAI_Result'
EXEC sp_addextendedproperty N'MS_Description', '前右轮转角左转数值', N'user', N'dbo', N'table', N'NCAResult', N'column', N'RTAO'
EXEC sp_addextendedproperty N'MS_Description', '前右轮转角左转评判', N'user', N'dbo', N'table', N'NCAResult', N'column', N'RTAO_Result'
EXEC sp_addextendedproperty N'MS_Description', '总评', N'user', N'dbo', N'table', N'NCAResult', N'column', N'Result'
GO

-- 测试: 插入数据
INSERT JAC.dbo.NCAResult
    VALUES (
		'testvincode012345',
		'VSN',
		'2013-03-17 10:41:08',
		'IEV7S',
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
		'O',
		3.2,
		'O',
		3.2,
		'O',
		-3.3,
		'O',
		3.2,
		'O',
		3.2,
		'O',
		-34.3,
		'O',
		34.3,
		'O',
		34.3,
		'O',
		-34.3,
		'O',
		'O'
	)
GO
-- 测试: 查询数据
SELECT *
    FROM JAC.dbo.NCAResult
GO

-- 灯光仪测试结果表
IF OBJECT_ID(N'JAC.dbo.HLAResult') IS NOT NULL
    DROP TABLE JAC.dbo.HLAResult
GO
CREATE TABLE JAC.dbo.HLAResult
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
	VINCODE varchar(17) NOT NULL, -- VIN码
	Vehicle varchar(30) NULL, -- 车辆
	InspectDate DATE NULL, -- 检测日期
	InspectTime TIME NULL, -- 检测时间

	LLowHor float NULL, -- 左灯近光水平偏移数值
	LLowHor_Result char(1) NULL, -- 左灯近光水平偏移评判, O是合格, X是不合格, 福瑞INI文件里是“LLowHor-Result”
	LLowVer float NULL, -- 左灯近光垂直偏移数值
	LLowVer_Result char(1) NULL, -- 左灯近光垂直偏移评判, O是合格, X是不合格, 福瑞INI文件里是“LLowVer-Result”
	LLowInten float NULL, -- 左灯近光光强数值, 福瑞INI文件里是“LLowIten”
	LLowInten_Result char(1) NULL, -- 左灯近光光强评判, O是合格, X是不合格, 福瑞INI文件里是“LLowIten-Result”
	LHighHor float NULL, -- 左灯远光水平偏移数值
	LHighHor_Result char(1) NULL, -- 左灯远光水平偏移评判, O是合格, X是不合格, 福瑞INI文件里是“LHighHor-Result”
	LHighVer float NULL, -- 左灯远光垂直偏移数值
	LHighVer_Result char(1) NULL, -- 左灯远光垂直偏移评判, O是合格, X是不合格, 福瑞INI文件里是“LHighVer-Result”
	LHighInten float NULL, -- 左灯远光光强数值, 福瑞INI文件里是“LHighIten”
	LHighInten_Result char(1) NULL, -- 左灯远光光强评判, O是合格, X是不合格, 福瑞INI文件里是“LHighIten-Result”
	RLowHor float NULL, -- 右灯近光水平偏移数值
	RLowHor_Result char(1) NULL, -- 右灯近光水平偏移评判, O是合格, X是不合格, 福瑞INI文件里是“RLowHor-Result”
	RLowVer float NULL, -- 右灯近光垂直偏移数值
	RLowVer_Result char(1) NULL, -- 右灯近光垂直偏移评判, O是合格, X是不合格, 福瑞INI文件里是“RLowVer-Result”
	RLowInten float NULL, -- 右灯近光光强数值, 福瑞INI文件里是“RLowIten”
	RLowInten_Result char(1) NULL, -- 右灯近光光强评判, O是合格, X是不合格, 福瑞INI文件里是“RLowIten-Result”
	RHighHor float NULL, -- 右灯远光水平偏移数值
	RHighHor_Result char(1) NULL, -- 右灯远光水平偏移评判, O是合格, X是不合格, 福瑞INI文件里是“RHighHor-Result”
	RHighVer float NULL, -- 右灯远光垂直偏移数值
	RHighVer_Result char(1) NULL, -- 右灯远光垂直偏移评判, O是合格, X是不合格, 福瑞INI文件里是“RHighVer-Result”
	RHighInten float NULL, -- 右灯远光光强数值, 福瑞INI文件里是“RHighIten”
	RHighInten_Result char(1) NULL, -- 右灯远光光强评判, O是合格, X是不合格, 福瑞INI文件里是“RHighIten-Result”
	LFogHor float NULL, -- 左灯雾灯水平偏移数值
	LFogHor_Result char(1) NULL, -- 左灯雾灯水平偏移评判, O是合格, X是不合格, 福瑞INI文件里是“LFogHor-Result”
	LFogVer float NULL, -- 左灯雾灯垂直偏移数值
	LFogVer_Result char(1) NULL, -- 左灯雾灯垂直偏移评判, O是合格, X是不合格, 福瑞INI文件里是“LFogVer-Result”
	LFogInten float NULL, -- 左灯雾灯光强数值
	LFogInten_Result char(1) NULL, -- 左灯雾灯光强评判, O是合格, X是不合格, 福瑞INI文件里是“LFogIten-Result”
	RFogHor float NULL, -- 右灯雾灯水平偏移数值
	RFogHor_Result char(1) NULL, -- 右灯雾灯水平偏移评判, O是合格, X是不合格, 福瑞INI文件里是“RFogHor-Result”
	RFogVer float NULL, -- 右灯雾灯垂直偏移数值
	RFogVer_Result char(1) NULL, -- 右灯雾灯垂直偏移评判, O是合格, X是不合格, 福瑞INI文件里是“RFogVer-Result”
	RFogInten float NULL, -- 右灯雾灯光强数值, 福瑞INI文件里是“RFogIten”
	RFogInten_Result char(1) NULL, -- 右灯雾灯光强评判, O是合格, X是不合格, 福瑞INI文件里是“RFogIten-Result”
	Total_Result char(1) NULL, -- 灯光总评, O是合格, X是不合格, 福瑞INI文件里是“Total Result”
)
GO

-- 插入字段备注
EXEC sp_addextendedproperty N'MS_Description', 'ID', N'user', N'dbo', N'table', N'HLAResult', N'column', N'ID'
EXEC sp_addextendedproperty N'MS_Description', 'VIN码', N'user', N'dbo', N'table', N'HLAResult', N'column', N'VINCODE'
EXEC sp_addextendedproperty N'MS_Description', '车辆', N'user', N'dbo', N'table', N'HLAResult', N'column', N'Vehicle'
EXEC sp_addextendedproperty N'MS_Description', '检测日期', N'user', N'dbo', N'table', N'HLAResult', N'column', N'InspectDate'
EXEC sp_addextendedproperty N'MS_Description', '检测时间', N'user', N'dbo', N'table', N'HLAResult', N'column', N'InspectTime'

EXEC sp_addextendedproperty N'MS_Description', '左灯近光水平偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LLowHor'
EXEC sp_addextendedproperty N'MS_Description', '左灯近光水平偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LLowHor_Result'
EXEC sp_addextendedproperty N'MS_Description', '左灯近光垂直偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LLowVer'
EXEC sp_addextendedproperty N'MS_Description', '左灯近光垂直偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LLowVer_Result'
EXEC sp_addextendedproperty N'MS_Description', '左灯近光光强数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LLowInten'
EXEC sp_addextendedproperty N'MS_Description', '左灯近光光强评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LLowInten_Result'
EXEC sp_addextendedproperty N'MS_Description', '左灯远光水平偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LHighHor'
EXEC sp_addextendedproperty N'MS_Description', '左灯远光水平偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LHighHor_Result'
EXEC sp_addextendedproperty N'MS_Description', '左灯远光垂直偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LHighVer'
EXEC sp_addextendedproperty N'MS_Description', '左灯远光垂直偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LHighVer_Result'
EXEC sp_addextendedproperty N'MS_Description', '左灯远光光强数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LHighInten'
EXEC sp_addextendedproperty N'MS_Description', '左灯远光光强评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LHighInten_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯近光水平偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RLowHor'
EXEC sp_addextendedproperty N'MS_Description', '右灯近光水平偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RLowHor_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯近光垂直偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RLowVer'
EXEC sp_addextendedproperty N'MS_Description', '右灯近光垂直偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RLowVer_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯近光光强数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RLowInten'
EXEC sp_addextendedproperty N'MS_Description', '右灯近光光强评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RLowInten_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯远光水平偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RHighHor'
EXEC sp_addextendedproperty N'MS_Description', '右灯远光水平偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RHighHor_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯远光垂直偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RHighVer'
EXEC sp_addextendedproperty N'MS_Description', '右灯远光垂直偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RHighVer_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯远光光强数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RHighInten'
EXEC sp_addextendedproperty N'MS_Description', '右灯远光光强评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RHighInten_Result'
EXEC sp_addextendedproperty N'MS_Description', '左灯雾灯水平偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LFogHor'
EXEC sp_addextendedproperty N'MS_Description', '左灯雾灯水平偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LFogHor_Result'
EXEC sp_addextendedproperty N'MS_Description', '左灯雾灯垂直偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LFogVer'
EXEC sp_addextendedproperty N'MS_Description', '左灯雾灯垂直偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LFogVer_Result'
EXEC sp_addextendedproperty N'MS_Description', '左灯雾灯光强数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LFogInten'
EXEC sp_addextendedproperty N'MS_Description', '左灯雾灯光强评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'LFogInten_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯雾灯水平偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RFogHor'
EXEC sp_addextendedproperty N'MS_Description', '右灯雾灯水平偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RFogHor_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯雾灯垂直偏移数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RFogVer'
EXEC sp_addextendedproperty N'MS_Description', '右灯雾灯垂直偏移评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RFogVer_Result'
EXEC sp_addextendedproperty N'MS_Description', '右灯雾灯光强数值', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RFogInten'
EXEC sp_addextendedproperty N'MS_Description', '右灯雾灯光强评判', N'user', N'dbo', N'table', N'HLAResult', N'column', 'RFogInten_Result'
EXEC sp_addextendedproperty N'MS_Description', '灯光总评', N'user', N'dbo', N'table', N'HLAResult', N'column', N'Total_Result'
GO

-- 测试: 插入数据
INSERT JAC.dbo.HLAResult
    VALUES (
		'testvincode012345',
		'Vehicle',
		'2013-03-17',
		'10:41:08',
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
		'O',
		'O'
	)
GO
-- 测试: 查询数据
SELECT *
    FROM JAC.dbo.HLAResult
GO

-- 侧滑台测试结果表
IF OBJECT_ID(N'JAC.dbo.SideSlipResult') IS NOT NULL
    DROP TABLE JAC.dbo.SideSlipResult
GO
CREATE TABLE JAC.dbo.SideSlipResult
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
	Vincode varchar(17) NOT NULL, -- VIN码
	VehicleType varchar(30) NOT NULL, -- 车型代码
	Additional_code varchar(30) NULL, -- 附加代码，福瑞INI文件内是“Additional code”
	InspectTimes int NULL, -- 检测次数
	InspectDate DATE NULL, -- 检测日期
	InspectTime TIME NULL, -- 检测时间

	FrontSlipValue float NULL, -- 前轴侧滑数值
	FrontSlipResult char(1) NULL, -- 前轴侧滑评判, O是合格, X是不合格
	FrontSpeedValue float NULL, -- 前轴速度数值
	FrontSpeedResult char(1) NULL, -- 前轴速度评判, O是合格, X是不合格
	RearSlipValue float NULL, -- 后轴侧滑数值
	RearSlipResult char(1) NULL, -- 后轴侧滑评判, O是合格, X是不合格
	RearSpeedValue float NULL, -- 后轴速度数值
	RearSpeedResult char(1) NULL, -- 后轴速度评判, O是合格, X是不合格
	SlipResult char(1) NULL, -- 侧滑总评, O是合格, X是不合格
)
GO

-- 插入字段备注
EXEC sp_addextendedproperty N'MS_Description', 'ID', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'ID'
EXEC sp_addextendedproperty N'MS_Description', 'VIN码', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'Vincode'
EXEC sp_addextendedproperty N'MS_Description', '车型代码', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'VehicleType'
EXEC sp_addextendedproperty N'MS_Description', '附加代码', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'Additional_code'
EXEC sp_addextendedproperty N'MS_Description', '检测次数', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'InspectTimes'
EXEC sp_addextendedproperty N'MS_Description', '检测日期', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'InspectDate'
EXEC sp_addextendedproperty N'MS_Description', '检测时间', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'InspectTime'

EXEC sp_addextendedproperty N'MS_Description', '前轴侧滑数值', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'FrontSlipValue'
EXEC sp_addextendedproperty N'MS_Description', '前轴侧滑评判', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'FrontSlipResult'
EXEC sp_addextendedproperty N'MS_Description', '前轴速度数值', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'FrontSpeedValue'
EXEC sp_addextendedproperty N'MS_Description', '前轴速度评判', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'FrontSpeedResult'
EXEC sp_addextendedproperty N'MS_Description', '后轴侧滑数值', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'RearSlipValue'
EXEC sp_addextendedproperty N'MS_Description', '后轴侧滑评判', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'RearSlipResult'
EXEC sp_addextendedproperty N'MS_Description', '后轴速度数值', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'RearSpeedValue'
EXEC sp_addextendedproperty N'MS_Description', '后轴速度评判', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'RearSpeedResult'
EXEC sp_addextendedproperty N'MS_Description', '侧滑总评', N'user', N'dbo', N'table', N'SideSlipResult', N'column', N'SlipResult'
GO

-- 测试: 插入数据
INSERT JAC.dbo.SideSlipResult
    VALUES (
		'testvincode012345',
		'IEV7S',
		'Additional code',
		1,
		'2013-03-17',
		'10:41:08',
		0.0,
		'O',
		3.4,
		'O',
		0.0,
		'O',
		3.4,
		'O',
		'O'
	)
GO
-- 测试: 查询数据
SELECT *
    FROM JAC.dbo.SideSlipResult
GO

-- 制动台测试结果表
IF OBJECT_ID(N'JAC.dbo.BrakeResult') IS NOT NULL
    DROP TABLE JAC.dbo.BrakeResult
GO
CREATE TABLE JAC.dbo.BrakeResult
(
	ID int IDENTITY PRIMARY KEY NOT NULL, -- ID, 自增, 主键
	Vincode varchar(17) NOT NULL, -- VIN码
	InspectorNo varchar(30) NULL, -- 检测号
	VehicleType varchar(30) NOT NULL, -- 车型代码
	InspectTimes int NULL, -- 检测次数
	InspectDate DATETIME NULL, -- 检测日期时间
	InspectTime TIME NULL, -- 检测时间
	ABSEnable char(1) NULL, -- 是否检测ABS, Y是, N否
	BrakeEnable char(1) NULL, -- 是否检测制动, Y是, N否
	Abort char(1) NULL, -- 是否放弃检测, Y是, N否

	Weight1LeftValue float NULL, -- 前轴左轮轮重数据
	Weight1RightValue float NULL, -- 前轴右轮轮重数据
	Weight1TotalValue float NULL, -- 前轴总轮重数据
	Brake1LeftMaxSumForce float NULL, -- 前轴最大制动和时左轮的制动力
	Brake1RightMaxSumForce float NULL, -- 前轴最大制动和时右轮的制动力
	Brake1LeftMaxDiffForce float NULL, -- 前轴最大制动差时左轮的制动力
	Brake1RightMaxDiffForce float NULL, -- 前轴最大制动差时右轮的制动力
	Brake1LeftMaxDragForce float NULL, -- 前轴左轮最大阻滞力数值
	Brake1RightMaxDragForce float NULL, -- 前轴右轮最大阻滞力数值
	Brake1LeftDragValue float NULL, -- 前轴左轮阻滞率数值
	Brake1LeftDragResult char(1) NULL, -- 前轴左轮阻滞率评判, O是合格, X是不合格
	Brake1RightDragValue float NULL, -- 前轴右轮阻滞率数值
	Brake1RightDragResult char(1) NULL, -- 前轴右轮阻滞率评判, O是合格, X是不合格
	Brake1MaxSumValue float NULL, -- 前轴最大制动和数值
	Brake1MaxDiffValue float NULL, -- 前轴最大制动差数值
	Brake1MaxSumResult char(1) NULL, -- 前轴最大制动和评判, O是合格, X是不合格
	Brake1MaxDiffResult char(1) NULL, -- 前轴最大制动差评判, O是合格, X是不合格
	Brake1MaxForce float NULL, -- 前轴制动过程中的最大制动力
	Brake1MotorStopFlag char(1) NULL, -- 前轴马达停止标志, Y是, N否
	Brake1Result char(1) NULL, -- 前轴制动评判, O是合格, X是不合格

	Weight4LeftValue float NULL, -- 后轴左轮轮重数据
	Weight4RightValue float NULL, -- 后轴右轮轮重数据
	Weight4TotalValue float NULL, -- 后轴总轮重数据
	Brake4LeftMaxSumForce float NULL, -- 后轴最大制动和时左轮的制动力
	Brake4RightMaxSumForce float NULL, -- 后轴最大制动和时右轮的制动力
	Brake4LeftMaxDiffForce float NULL, -- 后轴最大制动差时左轮的制动力
	Brake4RightMaxDiffForce float NULL, -- 后轴最大制动差时右轮的制动力
	Brake4LeftMaxDragForce float NULL, -- 后左轮最大阻滞力数值
	Brake4RightMaxDragForce float NULL, -- 后右轮最大阻滞力数值
	Brake4LeftDragValue float NULL, -- 后轴左轮阻滞率数值
	Brake4LeftDragResult char(1) NULL, -- 后轴左轮阻滞率评判, O是合格, X是不合格
	Brake4RightDragValue float NULL, -- 后轴右轮阻滞率数值
	Brake4RightDragResult char(1) NULL, -- 后轴右轮阻滞率评判, O是合格, X是不合格
	Brake4MaxSumValue float NULL, -- 后轴最大制动和数值
	Brake4MaxDiffValue float NULL, -- 后轴最大制动差数值
	Brake4MaxSumResult char(1) NULL, -- 后轴最大制动和评判, O是合格, X是不合格
	Brake4MaxDiffResult char(1) NULL, -- 后轴最大制动差评判, O是合格, X是不合格
	Brake4MaxForce float NULL, -- 后轴制动过程中的最大制动力
	Brake4MotorStopFlag char(1) NULL, -- 后轴马达停止标志, Y是, N否
	Brake4Result char(1) NULL, -- 后轴制动评判, O是合格, X是不合格

	Weight5LeftValue float NULL, -- 驻车左轮轮重数据
	Weight5RightValue float NULL, -- 驻车右轮轮重数据
	Weight5TotalValue float NULL, -- 驻车总轮重数据
	Brake5LeftMaxSumForce float NULL, -- 驻车最大制动和时左轮的制动力
	Brake5RightMaxSumForce float NULL, -- 驻车最大制动和时右轮的制动力
	Brake5LeftMaxDiffForce float NULL, -- 驻车最大制动差时左轮的制动力
	Brake5RightMaxDiffForce float NULL, -- 驻车最大制动差时右轮的制动力
	Brake5LeftMaxDragForce float NULL, -- 驻车轮最大阻滞力数值
	Brake5RightMaxDragForce float NULL, -- 驻车轮最大阻滞力数值
	Brake5LeftDragValue float NULL, -- 驻车左轮阻滞率数值
	Brake5LeftDragResult char(1) NULL, -- 驻车左轮阻滞率评判, O是合格, X是不合格
	Brake5RightDragValue float NULL, -- 驻车右轮阻滞率数值
	Brake5RightDragResult char(1) NULL, -- 驻车右轮阻滞率评判, O是合格, X是不合格
	Brake5MaxSumValue float NULL, -- 驻车最大制动和数值
	Brake5MaxDiffValue float NULL, -- 驻车最大制动差数值
	Brake5MaxSumResult char(1) NULL, -- 驻车最大制动和评判, O是合格, X是不合格
	Brake5MaxDiffResult char(1) NULL, -- 驻车最大制动差评判, O是合格, X是不合格
	Brake5MaxForce float NULL, -- 驻车制动过程中的最大制动力
	Brake5MotorStopFlag char(1) NULL, -- 驻车马达停止标志, Y是, N否
	Brake5Result char(1) NULL, -- 驻车制动评判, O是合格, X是不合格

	TotalSumValue float NULL, -- 整车制动和数值
	TotalSumResult char(1) NULL, -- 整车制动和评判, O是合格, X是不合格
	PedalEnable char(1) NULL, -- 是否检测踏板力, Y是, N否
	FrontPedalValue float NULL, -- 前轴踏板力数值
	FrontPedalResult char(1) NULL, -- 前轴踏板力评判, O是合格, X是不合格
	RearPedalValue float NULL, -- 后轴踏板力数值
	RearPedalResult char(1) NULL, -- 后轴踏板力评判, O是合格, X是不合格
	DragParkEnable char(1) NULL, -- 是否检测手拉力, Y是, N否
	DragParkValue float NULL, -- 手拉力数值
	DragParkResult char(1) NULL, -- 手拉力评判, O是合格, X是不合格
	BrakeResult char(1) NULL, -- 制动部分评判, O是合格, X是不合格
	TotalResult char(1) NULL, -- 制动总评, O是合格, X是不合格
	FrontResponseTime float NULL, -- 前轴制动协调时间数值
	RearResponseTime float NULL, -- 后轴制动协调时间数值
)
GO

-- 插入字段备注
EXEC sp_addextendedproperty N'MS_Description', 'ID', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'ID'
EXEC sp_addextendedproperty N'MS_Description', 'VIN码', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'Vincode'
EXEC sp_addextendedproperty N'MS_Description', '检测号', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'InspectorNo'
EXEC sp_addextendedproperty N'MS_Description', '车型代码', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'VehicleType'
EXEC sp_addextendedproperty N'MS_Description', '检测次数', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'InspectTimes'
EXEC sp_addextendedproperty N'MS_Description', '检测日期', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'InspectDate'
EXEC sp_addextendedproperty N'MS_Description', '检测时间', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'InspectTime'
EXEC sp_addextendedproperty N'MS_Description', '是否检测ABS', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'ABSEnable'
EXEC sp_addextendedproperty N'MS_Description', '是否检测制动', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'BrakeEnable'
EXEC sp_addextendedproperty N'MS_Description', '是否放弃检测', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'Abort'

EXEC sp_addextendedproperty N'MS_Description', '前轴左轮轮重数据', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Weight1LeftValue'
EXEC sp_addextendedproperty N'MS_Description', '前轴右轮轮重数据', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Weight1RightValue'
EXEC sp_addextendedproperty N'MS_Description', '前轴总轮重数据', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Weight1TotalValue'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动和时左轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1LeftMaxSumForce'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动和时右轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1RightMaxSumForce'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动差时左轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1LeftMaxDiffForce'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动差时右轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1RightMaxDiffForce'
EXEC sp_addextendedproperty N'MS_Description', '前轴左轮最大阻滞力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1LeftMaxDragForce'
EXEC sp_addextendedproperty N'MS_Description', '前轴右轮最大阻滞力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1RightMaxDragForce'
EXEC sp_addextendedproperty N'MS_Description', '前轴左轮阻滞率数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1LeftDragValue'
EXEC sp_addextendedproperty N'MS_Description', '前轴左轮阻滞率评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1LeftDragResult'
EXEC sp_addextendedproperty N'MS_Description', '前轴右轮阻滞率数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1RightDragValue'
EXEC sp_addextendedproperty N'MS_Description', '前轴右轮阻滞率评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1RightDragResult'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动和数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1MaxSumValue'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动差数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1MaxDiffValue'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动和评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1MaxSumResult'
EXEC sp_addextendedproperty N'MS_Description', '前轴最大制动差评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1MaxDiffResult'
EXEC sp_addextendedproperty N'MS_Description', '前轴制动过程中的最大制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1MaxForce'
EXEC sp_addextendedproperty N'MS_Description', '前轴马达停止标志', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1MotorStopFlag'
EXEC sp_addextendedproperty N'MS_Description', '前轴制动评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake1Result'

EXEC sp_addextendedproperty N'MS_Description', '后轴左轮轮重数据', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Weight4LeftValue'
EXEC sp_addextendedproperty N'MS_Description', '后轴右轮轮重数据', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Weight4RightValue'
EXEC sp_addextendedproperty N'MS_Description', '后轴总轮重数据', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Weight4TotalValue'
EXEC sp_addextendedproperty N'MS_Description', '后轴最大制动和时左轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4LeftMaxSumForce'
EXEC sp_addextendedproperty N'MS_Description', '后轴最大制动和时右轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4RightMaxSumForce'
EXEC sp_addextendedproperty N'MS_Description', '后轴最大制动差时左轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4LeftMaxDiffForce'
EXEC sp_addextendedproperty N'MS_Description', '后轴最大制动差时右轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4RightMaxDiffForce'
EXEC sp_addextendedproperty N'MS_Description', '后轴左轮最大阻滞力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4LeftMaxDragForce'
EXEC sp_addextendedproperty N'MS_Description', '后轴右轮最大阻滞力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4RightMaxDragForce'
EXEC sp_addextendedproperty N'MS_Description', '后轴左轮阻滞率数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4LeftDragValue'
EXEC sp_addextendedproperty N'MS_Description', '后轴左轮阻滞率评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4LeftDragResult'
EXEC sp_addextendedproperty N'MS_Description', '后轴右轮阻滞率数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4RightDragValue'
EXEC sp_addextendedproperty N'MS_Description', '后轴右轮阻滞率评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4RightDragResult'
EXEC sp_addextendedproperty N'MS_Description', '后轴最大制动和数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4MaxSumValue'
EXEC sp_addextendedproperty N'MS_Description', '后轴最大制动差数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4MaxDiffValue'
EXEC sp_addextendedproperty N'MS_Description', '后轴最大制动和评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4MaxSumResult'
EXEC sp_addextendedproperty N'MS_Description', '后轴最大制动差评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4MaxDiffResult'
EXEC sp_addextendedproperty N'MS_Description', '后轴制动过程中的最大制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4MaxForce'
EXEC sp_addextendedproperty N'MS_Description', '后轴马达停止标志', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4MotorStopFlag'
EXEC sp_addextendedproperty N'MS_Description', '后轴制动评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake4Result'

EXEC sp_addextendedproperty N'MS_Description', '驻车左轮轮重数据', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Weight5LeftValue'
EXEC sp_addextendedproperty N'MS_Description', '驻车右轮轮重数据', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Weight5RightValue'
EXEC sp_addextendedproperty N'MS_Description', '驻车总轮重数据', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Weight5TotalValue'
EXEC sp_addextendedproperty N'MS_Description', '驻车最大制动和时左轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5LeftMaxSumForce'
EXEC sp_addextendedproperty N'MS_Description', '驻车最大制动和时右轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5RightMaxSumForce'
EXEC sp_addextendedproperty N'MS_Description', '驻车最大制动差时左轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5LeftMaxDiffForce'
EXEC sp_addextendedproperty N'MS_Description', '驻车最大制动差时右轮的制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5RightMaxDiffForce'
EXEC sp_addextendedproperty N'MS_Description', '驻车左轮最大阻滞力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5LeftMaxDragForce'
EXEC sp_addextendedproperty N'MS_Description', '驻车右轮最大阻滞力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5RightMaxDragForce'
EXEC sp_addextendedproperty N'MS_Description', '驻车左轮阻滞率数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5LeftDragValue'
EXEC sp_addextendedproperty N'MS_Description', '驻车左轮阻滞率评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5LeftDragResult'
EXEC sp_addextendedproperty N'MS_Description', '驻车右轮阻滞率数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5RightDragValue'
EXEC sp_addextendedproperty N'MS_Description', '驻车右轮阻滞率评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5RightDragResult'
EXEC sp_addextendedproperty N'MS_Description', '驻车最大制动和数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5MaxSumValue'
EXEC sp_addextendedproperty N'MS_Description', '驻车最大制动差数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5MaxDiffValue'
EXEC sp_addextendedproperty N'MS_Description', '驻车最大制动和评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5MaxSumResult'
EXEC sp_addextendedproperty N'MS_Description', '驻车最大制动差评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5MaxDiffResult'
EXEC sp_addextendedproperty N'MS_Description', '驻车制动过程中的最大制动力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5MaxForce'
EXEC sp_addextendedproperty N'MS_Description', '驻车马达停止标志', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5MotorStopFlag'
EXEC sp_addextendedproperty N'MS_Description', '驻车制动评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'Brake5Result'

EXEC sp_addextendedproperty N'MS_Description', '整车制动和数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'TotalSumValue'
EXEC sp_addextendedproperty N'MS_Description', '整车制动和评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'TotalSumResult'
EXEC sp_addextendedproperty N'MS_Description', '是否检测踏板力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'PedalEnable'
EXEC sp_addextendedproperty N'MS_Description', '前轴踏板力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FrontPedalValue'
EXEC sp_addextendedproperty N'MS_Description', '前轴踏板力评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FrontPedalResult'
EXEC sp_addextendedproperty N'MS_Description', '后轴踏板力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RearPedalValue'
EXEC sp_addextendedproperty N'MS_Description', '后轴踏板力评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RearPedalResult'
EXEC sp_addextendedproperty N'MS_Description', '是否检测手拉力', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'DragParkEnable'
EXEC sp_addextendedproperty N'MS_Description', '手拉力数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'DragParkValue'
EXEC sp_addextendedproperty N'MS_Description', '手拉力评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'DragParkResult'
EXEC sp_addextendedproperty N'MS_Description', '制动部分评判', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'BrakeResult'
EXEC sp_addextendedproperty N'MS_Description', '制动总评', N'user', N'dbo', N'table', N'BrakeResult', N'column', N'TotalResult'
EXEC sp_addextendedproperty N'MS_Description', '前轴制动协调时间数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'FrontResponseTime'
EXEC sp_addextendedproperty N'MS_Description', '后轴制动协调时间数值', N'user', N'dbo', N'table', N'BrakeResult', N'column', 'RearResponseTime'
GO

-- 测试: 插入数据
INSERT JAC.dbo.BrakeResult
    VALUES (
		'testvincode012345',
		'InspectorNo',
		'IEV7S',
		1,
		'2013-03-17',
		'10:41:08',
		'N',
		'Y',
		'N',
		478.1,
		453.2,
		478.3,
		453.4,
		372.5,
		415.6,
		149.7,
		166.8,
		420.9,
		14.4,
		'O',
		14.6,
		'O',
		1.5,
		4.1,
		'O',
		'O',
		420.5,
		'N',
		'X',
		478.1,
		453.2,
		478.3,
		453.4,
		372.5,
		415.6,
		149.7,
		166.8,
		420.9,
		14.4,
		'O',
		14.6,
		'O',
		1.5,
		4.1,
		'O',
		'O',
		420.4,
		'N',
		'X',
		478.1,
		453.2,
		478.3,
		453.4,
		372.5,
		415.6,
		149.7,
		166.8,
		420.9,
		14.4,
		'O',
		14.6,
		'O',
		1.5,
		4.1,
		'O',
		'O',
		420.3,
		'N',
		'X',
		230.6,
		'O',
		'N',
		23.4,
		'O',
		23.4,
		'O',
		'N',
		75.7,
		'O',
		'O',
		'O',
		0.8,
		0.8
	)
GO
-- 测试: 查询数据
SELECT *
    FROM JAC.dbo.BrakeResult
GO
