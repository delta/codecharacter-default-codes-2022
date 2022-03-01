public class SpawnDetail {
    private int typeId;
    private Position pos;

    public SpawnDetail(int typeId, Position pos) {
        this.typeId = typeId;
        this.pos = pos;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        SpawnDetail other = (SpawnDetail) obj;
        if (pos == null) {
            if (other.pos != null)
                return false;
        } else if (!pos.equals(other.pos))
            return false;
        if (typeId != other.typeId)
            return false;
        return true;
    }

    public int getTypeId() {
        return typeId;
    }

    public Position getPos() {
        return pos;
    }

}
