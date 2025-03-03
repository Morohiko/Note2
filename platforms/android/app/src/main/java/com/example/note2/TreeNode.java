package com.example.note2;

import java.util.ArrayList;
import java.util.List;

public class TreeNode {
    private String text;
    private List<TreeNode> children;

    public TreeNode(String text) {
        this.text = text;
        this.children = new ArrayList<>();
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public List<TreeNode> getChildren() {
        return children;
    }
}
