package com.mayinlong.utils;



import java.sql.SQLException;

import javax.sql.DataSource;

import com.mchange.v2.c3p0.ComboPooledDataSource;
import com.sun.jdi.connect.spi.Connection;

/**
 * C3p0工具类
 * @author Admin
 *
 */
public class C3p0Tool {
	/**
	 * 获取数据源
	 */
	private static DataSource dataSource =new ComboPooledDataSource();
	public static DataSource getDataSource() {
		return dataSource;
	}
	/**
	 * 获取连接
	 * @return
	 */
	public static Connection getConnection() {
		try {
			return (Connection) dataSource.getConnection();
		} catch (SQLException e) {
			e.printStackTrace();
			throw new RuntimeException();
		}
		
	}
}
