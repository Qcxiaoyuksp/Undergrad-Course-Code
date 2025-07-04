package com.service;

import com.baomidou.mybatisplus.mapper.Wrapper;
import com.baomidou.mybatisplus.service.IService;
import com.utils.PageUtils;
import com.entity.JiangzuoleixingEntity;
import java.util.List;
import java.util.Map;
import com.entity.vo.JiangzuoleixingVO;
import org.apache.ibatis.annotations.Param;
import com.entity.view.JiangzuoleixingView;


/**
 * 讲座类型
 *
 * @author 
 * @email 
 * @date 2022-07-22 17:12:23
 */
public interface JiangzuoleixingService extends IService<JiangzuoleixingEntity> {

    PageUtils queryPage(Map<String, Object> params);
    
   	List<JiangzuoleixingVO> selectListVO(Wrapper<JiangzuoleixingEntity> wrapper);
   	
   	JiangzuoleixingVO selectVO(@Param("ew") Wrapper<JiangzuoleixingEntity> wrapper);
   	
   	List<JiangzuoleixingView> selectListView(Wrapper<JiangzuoleixingEntity> wrapper);
   	
   	JiangzuoleixingView selectView(@Param("ew") Wrapper<JiangzuoleixingEntity> wrapper);
   	
   	PageUtils queryPage(Map<String, Object> params,Wrapper<JiangzuoleixingEntity> wrapper);
   	

}

