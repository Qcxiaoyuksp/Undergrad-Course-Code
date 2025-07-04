package com.mayinlong.dao;

import java.sql.SQLException;
import java.util.List;

import org.apache.commons.dbutils.BasicRowProcessor;
import org.apache.commons.dbutils.BeanProcessor;
import org.apache.commons.dbutils.GenerousBeanProcessor;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.RowProcessor;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;
import org.apache.commons.dbutils.handlers.ScalarHandler;

import com.mayinlong.entity.UserDB;
import com.mayinlong.utils.C3p0Tool;
import com.mayinlong.utils.PageTool;


/**
 * 
 * 
 * 用户的数据连接层
 * @author Admin
 *
 */
public class UserDao {
	QueryRunner queryRunner = new QueryRunner(C3p0Tool.getDataSource());
	BeanProcessor bean = new GenerousBeanProcessor();
	RowProcessor processor = new BasicRowProcessor(bean);
	
	public UserDB login(String account, String password) {
		String sql = "select * from t_user where account = ? and password = ?";
		Object[] params = {account, password};
		try {
			return queryRunner.query(sql, new BeanHandler<UserDB>(UserDB.class, processor), params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return  null;
	}
	
	/**
	 * 异步校验
	 * @param userDB
	 * @return
	 */
	public List<UserDB> getList(UserDB userDB){
		String sql = "select * from t_user where account = ?";
		Object[] params = {userDB.getAccount()};
		try {
			return queryRunner.query(sql, new BeanListHandler<UserDB>(UserDB.class, processor),params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	/**
	 * 用户列表
	 * @return
	 */
	public PageTool<UserDB> list(String currentPage, String pageSize){
		try {
			StringBuffer listSql = new StringBuffer("select * ");
			StringBuffer countSql = new StringBuffer("select count(*) ");
			StringBuffer sql = new StringBuffer("from t_user");
			
			//获取总记录数
			Long total = queryRunner.query(countSql.append(sql).toString(), new ScalarHandler<Long>());
			//初始化分页工具
			PageTool<UserDB> pageTools = new PageTool<UserDB>(total.intValue(), currentPage, pageSize);
			sql.append(" limit ?,?");
			//当前页的数据		
			 List<UserDB> list = queryRunner.query(listSql.append(sql).toString(), new BeanListHandler<UserDB>(UserDB.class, processor),pageTools.getStartIndex(),pageTools.getPageSize());
			 pageTools.setRows(list);
			 System.out.println(pageTools);
			 return pageTools;
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return new PageTool<UserDB>(0, currentPage, pageSize);
	}
	/**
	 * 添加用户
	 * @param userDB
	 * @return
	 */
	public Integer addUser(UserDB userDB) {
		String sql = "insert into t_user (account,password,name,phone,times,role,address,graduate,age,email) values (?,?,?,?,?,?,?,?,?,?)";
		Object[] params = {userDB.getAccount(),userDB.getPassword(),userDB.getName(),userDB.getPhone(),userDB.getTimes(),userDB.getRole(),userDB.getAddress(),userDB.getGraduate(),userDB.getAge(),userDB.getEmail()};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	
	/**
	 * 管理员修改用户信息
	 * @param userDB
	 * @return
	 */
	public Integer updUser(UserDB userDB) {
		String sql = "update t_user set phone = ?, address = ?,graduate = ?,age = ?,email = ? where uid = ?";
		Object[] params = {userDB.getPhone(),userDB.getUid(),userDB.getAddress(),userDB.getGraduate(),userDB.getAge(),userDB.getEmail()};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	
	//开启驼峰自动转换
	public int delUser(Integer uid) {
		String sql = "delete from t_user where uid = ?";
		Object[] params = {uid};
		try {
			return queryRunner.update(sql, params);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return -1;
	}

}
