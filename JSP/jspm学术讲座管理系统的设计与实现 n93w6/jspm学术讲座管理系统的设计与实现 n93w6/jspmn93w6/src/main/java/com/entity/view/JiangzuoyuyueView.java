package com.entity.view;

import com.entity.JiangzuoyuyueEntity;

import com.baomidou.mybatisplus.annotations.TableName;
import org.apache.commons.beanutils.BeanUtils;
import java.lang.reflect.InvocationTargetException;

import java.io.Serializable;
 

/**
 * 讲座预约
 * 后端返回视图实体辅助类   
 * （通常后端关联的表或者自定义的字段需要返回使用）
 * @author 
 * @email 
 * @date 2022-07-22 17:12:23
 */
@TableName("jiangzuoyuyue")
public class JiangzuoyuyueView  extends JiangzuoyuyueEntity implements Serializable {
	private static final long serialVersionUID = 1L;

	public JiangzuoyuyueView(){
	}
 
 	public JiangzuoyuyueView(JiangzuoyuyueEntity jiangzuoyuyueEntity){
 	try {
			BeanUtils.copyProperties(this, jiangzuoyuyueEntity);
		} catch (IllegalAccessException | InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
 		
	}
}
