package com.dao;

import com.entity.JiangzuoleixingEntity;
import com.baomidou.mybatisplus.mapper.BaseMapper;
import java.util.List;
import java.util.Map;
import com.baomidou.mybatisplus.mapper.Wrapper;
import com.baomidou.mybatisplus.plugins.pagination.Pagination;

import org.apache.ibatis.annotations.Param;
import com.entity.vo.JiangzuoleixingVO;
import com.entity.view.JiangzuoleixingView;


/**
 * 讲座类型
 * 
 * @author 
 * @email 
 * @date 2022-07-22 17:12:23
 */
public interface JiangzuoleixingDao extends BaseMapper<JiangzuoleixingEntity> {
	
	List<JiangzuoleixingVO> selectListVO(@Param("ew") Wrapper<JiangzuoleixingEntity> wrapper);
	
	JiangzuoleixingVO selectVO(@Param("ew") Wrapper<JiangzuoleixingEntity> wrapper);
	
	List<JiangzuoleixingView> selectListView(@Param("ew") Wrapper<JiangzuoleixingEntity> wrapper);

	List<JiangzuoleixingView> selectListView(Pagination page,@Param("ew") Wrapper<JiangzuoleixingEntity> wrapper);
	
	JiangzuoleixingView selectView(@Param("ew") Wrapper<JiangzuoleixingEntity> wrapper);
	

}
