package com.zqc.dao;

import com.zqc.entity.SystemAdmin;

public interface SystemAdminDao {
    public SystemAdmin findByUserID(String userID);
    public Integer register(SystemAdmin systemAdmin);
}
