package com.entity.model;

import com.entity.JiangzuoxinxiEntity;

import com.baomidou.mybatisplus.annotations.TableName;
import com.fasterxml.jackson.annotation.JsonFormat;
import java.util.Date;
import org.springframework.format.annotation.DateTimeFormat;
import java.io.Serializable;
 

/**
 * 讲座信息
 * 接收传参的实体类  
 *（实际开发中配合移动端接口开发手动去掉些没用的字段， 后端一般用entity就够用了） 
 * 取自ModelAndView 的model名称
 * @author 
 * @email 
 * @date 2022-07-22 17:12:23
 */
public class JiangzuoxinxiModel  implements Serializable {
	private static final long serialVersionUID = 1L;

	 			
	/**
	 * 图片
	 */
	
	private String tupian;
		
	/**
	 * 讲座类型
	 */
	
	private String jiangzuoleixing;
		
	/**
	 * 讲座时间
	 */
		
	@JsonFormat(locale="zh", timezone="GMT+8", pattern="yyyy-MM-dd HH:mm:ss")
	@DateTimeFormat 
	private Date jiangzuoshijian;
		
	/**
	 * 人数
	 */
	
	private Integer renshu;
		
	/**
	 * 时长
	 */
	
	private String shizhang;
		
	/**
	 * 学术论文
	 */
	
	private String xueshulunwen;
		
	/**
	 * 主讲老师
	 */
	
	private String zhujianglaoshi;
		
	/**
	 * 讲座地点
	 */
	
	private String jiangzuodidian;
		
	/**
	 * 讲座详情
	 */
	
	private String jiangzuoxiangqing;
		
	/**
	 * 赞
	 */
	
	private Integer thumbsupnum;
		
	/**
	 * 踩
	 */
	
	private Integer crazilynum;
		
	/**
	 * 最近点击时间
	 */
		
	@JsonFormat(locale="zh", timezone="GMT+8", pattern="yyyy-MM-dd HH:mm:ss")
	@DateTimeFormat 
	private Date clicktime;
		
	/**
	 * 点击次数
	 */
	
	private Integer clicknum;
				
	
	/**
	 * 设置：图片
	 */
	 
	public void setTupian(String tupian) {
		this.tupian = tupian;
	}
	
	/**
	 * 获取：图片
	 */
	public String getTupian() {
		return tupian;
	}
				
	
	/**
	 * 设置：讲座类型
	 */
	 
	public void setJiangzuoleixing(String jiangzuoleixing) {
		this.jiangzuoleixing = jiangzuoleixing;
	}
	
	/**
	 * 获取：讲座类型
	 */
	public String getJiangzuoleixing() {
		return jiangzuoleixing;
	}
				
	
	/**
	 * 设置：讲座时间
	 */
	 
	public void setJiangzuoshijian(Date jiangzuoshijian) {
		this.jiangzuoshijian = jiangzuoshijian;
	}
	
	/**
	 * 获取：讲座时间
	 */
	public Date getJiangzuoshijian() {
		return jiangzuoshijian;
	}
				
	
	/**
	 * 设置：人数
	 */
	 
	public void setRenshu(Integer renshu) {
		this.renshu = renshu;
	}
	
	/**
	 * 获取：人数
	 */
	public Integer getRenshu() {
		return renshu;
	}
				
	
	/**
	 * 设置：时长
	 */
	 
	public void setShizhang(String shizhang) {
		this.shizhang = shizhang;
	}
	
	/**
	 * 获取：时长
	 */
	public String getShizhang() {
		return shizhang;
	}
				
	
	/**
	 * 设置：学术论文
	 */
	 
	public void setXueshulunwen(String xueshulunwen) {
		this.xueshulunwen = xueshulunwen;
	}
	
	/**
	 * 获取：学术论文
	 */
	public String getXueshulunwen() {
		return xueshulunwen;
	}
				
	
	/**
	 * 设置：主讲老师
	 */
	 
	public void setZhujianglaoshi(String zhujianglaoshi) {
		this.zhujianglaoshi = zhujianglaoshi;
	}
	
	/**
	 * 获取：主讲老师
	 */
	public String getZhujianglaoshi() {
		return zhujianglaoshi;
	}
				
	
	/**
	 * 设置：讲座地点
	 */
	 
	public void setJiangzuodidian(String jiangzuodidian) {
		this.jiangzuodidian = jiangzuodidian;
	}
	
	/**
	 * 获取：讲座地点
	 */
	public String getJiangzuodidian() {
		return jiangzuodidian;
	}
				
	
	/**
	 * 设置：讲座详情
	 */
	 
	public void setJiangzuoxiangqing(String jiangzuoxiangqing) {
		this.jiangzuoxiangqing = jiangzuoxiangqing;
	}
	
	/**
	 * 获取：讲座详情
	 */
	public String getJiangzuoxiangqing() {
		return jiangzuoxiangqing;
	}
				
	
	/**
	 * 设置：赞
	 */
	 
	public void setThumbsupnum(Integer thumbsupnum) {
		this.thumbsupnum = thumbsupnum;
	}
	
	/**
	 * 获取：赞
	 */
	public Integer getThumbsupnum() {
		return thumbsupnum;
	}
				
	
	/**
	 * 设置：踩
	 */
	 
	public void setCrazilynum(Integer crazilynum) {
		this.crazilynum = crazilynum;
	}
	
	/**
	 * 获取：踩
	 */
	public Integer getCrazilynum() {
		return crazilynum;
	}
				
	
	/**
	 * 设置：最近点击时间
	 */
	 
	public void setClicktime(Date clicktime) {
		this.clicktime = clicktime;
	}
	
	/**
	 * 获取：最近点击时间
	 */
	public Date getClicktime() {
		return clicktime;
	}
				
	
	/**
	 * 设置：点击次数
	 */
	 
	public void setClicknum(Integer clicknum) {
		this.clicknum = clicknum;
	}
	
	/**
	 * 获取：点击次数
	 */
	public Integer getClicknum() {
		return clicknum;
	}
			
}
