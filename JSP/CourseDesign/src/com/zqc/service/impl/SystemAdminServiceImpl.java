package com.zqc.service.impl;

import com.zqc.dao.SystemAdminDao;
import com.zqc.dao.impl.SystemAdminDaoImpl;
import com.zqc.dto.SystemAdminDto;
import com.zqc.entity.SystemAdmin;
import com.zqc.service.SystemAdminService;

public class SystemAdminServiceImpl implements SystemAdminService {
    private SystemAdminDao systemAdminDao = new SystemAdminDaoImpl();
    @Override
    public SystemAdminDto login(String userID, String password) {
        //1、通过username查询数据库
        //2、查询结果为空，username错误
        //3、查询结果不为空，再判断password是否正确
        SystemAdmin systemAdmin = this.systemAdminDao.findByUserID(userID);
        SystemAdminDto systemAdminDto = new SystemAdminDto();
        if(systemAdmin == null){
            //systemAdminDto.setMsg("工号/学号不存在");
            systemAdminDto.setCode(-1);
        } else {
            if(!systemAdmin.getPassword().equals(password)){
                //systemAdminDto.setMsg("密码错误");
                systemAdminDto.setCode(-2);
            } else {
                //systemAdminDto.setMsg("登录成功");
                systemAdminDto.setCode(0);
                systemAdminDto.setSystemAdmin(systemAdmin);
            }
        }
        return systemAdminDto;
    }

    @Override
    public void register(SystemAdmin systemAdmin) {
        Integer register = this.systemAdminDao.register(systemAdmin);
        if (register != 1) throw new RuntimeException("注册信息失败");
    }
}
