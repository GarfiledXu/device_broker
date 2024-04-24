import os
import sys
EXPECTED_MAJOR_VERSION = 2  # 预设主版本号
script_center_dir=r"./D-offline/script/python"
sys.path.append(script_center_dir)
from headeronly import *
version_check("2.0.0")

toolchain_dir_path=r'/home/xjf2613/code-space/qnx/qnx-arm-toolchain/qnx700/qnx700_sdp'
toolchain_file_path=os.path.join(toolchain_dir_path, r'qnx.toolchain.cmake')
custom_cmake_script_dir=r"D-offline/script/cmake"
other_module_list=[
    r'/home/xjf2613/code-space/QNX/qnx-sdk-project-20220228/FOR-PUBLIC/FOR_GTEST'
]

def qnx_make(build_target_list:list=[], other_module_list=other_module_list, custom_cmake_script_dir=r"D-offline/script/cmake", project_dir_path=os.path.dirname(os.path.abspath(__file__))):
    cfg1=(
        qnx_700_cfg() 
        .set_plat(toolchain_file_path, toolchain_dir_path) 
            .set_cmake_dir(project_dir_path) 
                .set_builder_type("debug") 
                    .set_builder_dir(project_dir_path + "/build") 
                        .define_var( 
                            exe_name = "new_exe_name", 
                            sys_name = "qnx", 
                            custom_cmake_script_dir = custom_cmake_script_dir, 
                            output_dir_root = r"out", 
                            cmake_file_root = custom_cmake_script_dir,
                            build_target_list = cvt_pylist_to_cmake(build_target_list),
                            other_module_list= cvt_pylist_to_cmake(other_module_list) 
                        )
    )
    CmakeRunner.clean_build(cfg1)
    CmakeRunner.generate(cfg1)
    CmakeRunner.build(cfg1, 8)
exe_dict = {
    # "o_sample": ["MAIN_SERVICE_qnx/Release/MAIN_SERVICE_qnx.exe"],
    # "o_gl_practice_1": ["practice_1/Release/practice_1.exe"],
}
##build usage: 在python脚本指定编译的target，
##可以在make函数的build_target_list的默认传输中直接指定, 需要带有o_前缀的target
##或者在命令行指定 -b (目标target的名称，去除了o_的target名称)
##依赖确定的顺序: 优先命令行，然后是python函数的默认参，然后是cmake脚本中target的指定
## e.g.   python focus.sh -b service

## run usage: 在python脚本中先指定dict，其为target对应的exe在根目录的相对路径
## 当dict中映射关系存在，则使用命令行 -r (要运行的target，除去o_前缀)
## e.g.   python focus.sh -r service  (由于交叉编译，这里无法使用)

##同时执行上两步
## e.g.  python focus.sh -t sample (由于交叉编译，这里无法使用)

if __name__=="__main__":
    args_module_parse(exe_dict, qnx_make)