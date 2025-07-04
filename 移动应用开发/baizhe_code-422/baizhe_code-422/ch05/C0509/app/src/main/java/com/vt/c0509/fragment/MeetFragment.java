package com.vt.c0509.fragment;

import android.os.Bundle;
import androidx.fragment.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import com.vt.c0509.R;

public class MeetFragment extends Fragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.fragment_meet, container, false);
        Button button = view.findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // ((MainActivity) getActivity()).showTabNum(2, 3);
                if (getContext() instanceof OnShowTabNumListener) {
                    OnShowTabNumListener onShowTabNumListener;
                    onShowTabNumListener = (OnShowTabNumListener) getContext();
                    onShowTabNumListener.onShowTabNum(2, 5);
                } else {
                    throw new RuntimeException(getContext().toString()
                            + " must implement OnShowTabNumListener");
                }
            }
        });
        return view;
    }
    //内部接口
    public interface OnShowTabNumListener {
        //定义接口方法
        void onShowTabNum(int index, int num);
    }
}