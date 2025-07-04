package com.zqc.service;

import com.zqc.dto.SystemAdminDto;
import com.zqc.entity.SystemAdmin;

public interface SystemAdminService {
    public SystemAdminDto login(String userID, String password);
    public void register(SystemAdmin systemAdmin);
}
