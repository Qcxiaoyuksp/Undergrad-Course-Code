package com.mayinlong.service;

import java.util.List;

import com.mayinlong.dao.UserDao;
import com.mayinlong.entity.UserDB;
import com.mayinlong.utils.PageTool;

public class UserService {
	private UserDao userDao = new UserDao();

	/**
	 * 登陆
	 * @param account
	 * @param password
	 * @return
	 */
	public UserDB login(String account, String password) {
		return userDao.login(account, password);
	}
	/**
	 * 用户添加
	 * @param userDB
	 * @return
	 */
	public Integer addUser(UserDB userDB) {
		return userDao.addUser(userDB);
	}
	
	
	/**
	 * 管理员修改用户信息
	 * @param userDB
	 * @return
	 */
	public Integer updUser(UserDB userDB) {
		return userDao.updUser(userDB);		
	}
	
	
	/**
	 * 删除用户-物理删除
	 * @param uid
	 * @return
	 */
	public Integer delUser(Integer uid) {
		return userDao.delUser(uid);
	}
	
	
	
	
	public PageTool<UserDB> list(String currentPage, String pageSize){
		return userDao.list(currentPage, pageSize);
	}
	public List<UserDB> getList(UserDB userDB){
		return userDao.getList(userDB);
	}
	
}
