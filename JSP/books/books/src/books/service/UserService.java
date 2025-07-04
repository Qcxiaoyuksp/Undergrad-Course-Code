package books.service;

import java.util.List;

import books.dao.UserDao;
import books.entity.UserDB; //实体
import books.utils.PageTool;

/*
 * 用户业务层
 * */
public class UserService {
	
	private UserDao userDao=new UserDao();
	
	//登陆
	public UserDB login(String account,String password)
	{
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
	
	//分页获取用户数据
	public PageTool<UserDB> list(String currentPage, String pageSize, Integer order){
		return userDao.list(currentPage, pageSize, order);
	}
	
	
	public List<UserDB> getList(UserDB userDB){
		return userDao.getList(userDB);
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
	 * 管理员删除用户-物理删除
	 * @param uid
	 * @return
	 */
	public Integer delUser(Integer uid) {
		return userDao.delUser(uid);
	}
	
	/*
	public List<UserDB> list(){
		return userDao.list();
	}*/

}
